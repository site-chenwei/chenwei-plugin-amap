package com.chenwei116057.plugin;

import android.app.Activity;
import android.content.Context;
import android.content.IntentFilter;
import android.net.ConnectivityManager;

import com.amap.api.fence.GeoFenceClient;
import com.amap.api.location.AMapLocationClient;
import com.amap.api.location.AMapLocationClientOption;
import com.amap.api.location.CoordinateConverter;
import com.amap.api.location.DPoint;
import com.amap.api.services.weather.WeatherSearch;
import com.amap.api.services.weather.WeatherSearchQuery;

import org.apache.cordova.*;
import org.json.JSONArray;
import org.json.JSONException;

import java.util.List;
import java.util.concurrent.ExecutorService;

public class AMapPlugin extends CordovaPlugin {
    private static final String TAG = "AMapPlugin";
    public static final String GEOFENCE_BROADCAST_ACTION = "com.chenwei116057.plugin.geofence.broadcast";
    private static Activity activity;
    private static Context context;
    private static ExecutorService threadPool;
    private IntentFilter filter;
    private AMapGeofenceListener aMapGeofenceListener;

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        activity = cordova.getActivity();
        context = cordova.getContext();
        threadPool = cordova.getThreadPool();
        LOG.i(TAG, "Plugin initialize success");
        aMapGeofenceListener = new AMapGeofenceListener();
        filter = new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION);
        filter.addAction(GEOFENCE_BROADCAST_ACTION);
        context.registerReceiver(aMapGeofenceListener, filter);
    }

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        LOG.i(TAG, "Plugin Received A New Action" + action);
        if (MethodNames.CALCULATE_DISTANCE.equalsIgnoreCase(action)) {
            PluginResult result = new PluginResult(PluginResult.Status.NO_RESULT);
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);
            calculateDistance(callbackContext, args);
        } else if (MethodNames.GET_LOCATION.equalsIgnoreCase(action)) {
            PluginResult result = new PluginResult(PluginResult.Status.NO_RESULT);
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);
            getLocation(callbackContext, args);
        } else if (MethodNames.GET_WEATHER_INFO.equalsIgnoreCase(action)) {
            PluginResult result = new PluginResult(PluginResult.Status.NO_RESULT);
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);
            getWeatherInfo(callbackContext, args);
        } else if (MethodNames.ADD_GEOFENCE.equalsIgnoreCase(action)) {
            PluginResult result = new PluginResult(PluginResult.Status.NO_RESULT);
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);
            addGeoFence(callbackContext, args);
        } else if (MethodNames.ON_GEOFENCE_RESULT.equalsIgnoreCase(action)) {
            PluginResult result = new PluginResult(PluginResult.Status.NO_RESULT);
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);
            onGeofenceResult(callbackContext, args);
        } else {
            LOG.i(TAG, "The Action" + action + "Not Exist");
            PluginResult result = new PluginResult(PluginResult.Status.INVALID_ACTION, "方法调用失败，不存在该方法");
            result.setKeepCallback(false);
            callbackContext.sendPluginResult(result);
        }
        return true;
    }

    private interface MethodNames {
        String GET_LOCATION = "getLocation";
        String GET_WEATHER_INFO = "getWeatherInfo";
        String CALCULATE_DISTANCE = "calculateDistance";
        String ADD_GEOFENCE = "addGeoFence";
        String ON_GEOFENCE_RESULT = "onGeofenceResult";
    }

    private void getLocation(CallbackContext callbackContext, JSONArray args) {
        AMapLocationClient aMapLocationClient = new AMapLocationClient(context);
        aMapLocationClient.setLocationListener(new AMapLocationListener(callbackContext, aMapLocationClient));
        AMapLocationClientOption aMapLocationClientOption = new AMapLocationClientOption().setLocationPurpose(AMapLocationClientOption.AMapLocationPurpose.SignIn);
        aMapLocationClientOption.setLocationMode(AMapLocationClientOption.AMapLocationMode.Hight_Accuracy);
        aMapLocationClientOption.setOnceLocationLatest(true);
        aMapLocationClientOption.setMockEnable(false);
        aMapLocationClientOption.setLocationCacheEnable(false);
        aMapLocationClientOption.setWifiActiveScan(true);
        aMapLocationClientOption.setWifiScan(true);
        aMapLocationClient.setLocationOption(aMapLocationClientOption);
        aMapLocationClient.stopLocation();
        aMapLocationClient.startLocation();
    }

    private void getWeatherInfo(CallbackContext callbackContext, JSONArray args) {
        try {
            WeatherSearchQuery weatherSearchQuery = new WeatherSearchQuery(args.getString(0), WeatherSearchQuery.WEATHER_TYPE_LIVE);
            WeatherSearch weatherSearch = new WeatherSearch(context);
            weatherSearch.setOnWeatherSearchListener(new AMapWeatherSearchListener(callbackContext));
            weatherSearch.setQuery(weatherSearchQuery);
            weatherSearch.searchWeatherAsyn();
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private void calculateDistance(CallbackContext callbackContext, JSONArray args) {
        try {
            DPoint startPoint = new DPoint(args.getDouble(0), args.getDouble(1));
            DPoint endPoint = new DPoint(args.getDouble(2), args.getDouble(3));
            float v = CoordinateConverter.calculateLineDistance(startPoint, endPoint);
            callbackContext.success(String.valueOf(v));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private void addGeoFence(CallbackContext callbackContext, JSONArray args) {
        try {
            DPoint point = new DPoint(args.getDouble(0), args.getDouble(1));
            int distance = args.getInt(2);
            String customId = args.getString(3);
            GeoFenceClient mGeoFenceClient = new GeoFenceClient(context);
            mGeoFenceClient.setGeoFenceListener(aMapGeofenceListener);
            mGeoFenceClient.createPendingIntent(GEOFENCE_BROADCAST_ACTION);
            mGeoFenceClient.addGeoFence(point, 100, customId);
            aMapGeofenceListener.onCreate(callbackContext, customId);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private void onGeofenceResult(CallbackContext callbackContext, JSONArray args) {
        aMapGeofenceListener.onReceive(callbackContext);
    }

}
