package com.chenwei116057.cordova.plugin;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Context;
import android.content.IntentFilter;
import android.net.ConnectivityManager;

import com.amap.api.fence.GeoFence;
import com.amap.api.fence.GeoFenceClient;
import com.amap.api.location.AMapLocationClient;
import com.amap.api.location.AMapLocationClientOption;
import com.amap.api.location.CoordinateConverter;
import com.amap.api.location.DPoint;
import com.amap.api.services.weather.WeatherSearch;
import com.amap.api.services.weather.WeatherSearchQuery;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.LOG;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;

import java.util.concurrent.ExecutorService;

public class AMapPlugin extends CordovaPlugin {
    private static final String TAG = "AMapPlugin";
    private static final String GEO_FENCE_BROADCAST_ACTION = "com.chenwei116057.cordova.plugin.broadcast";
    private static GeoFenceClient geoFenceInClient;
    private static GeoFenceClient geoFenceOutClient;
    private static GeoFenceClient geoFenceStayedClient;
    private static Activity activity;
    private static Context context;
    private static ExecutorService threadPool;

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        activity = cordova.getActivity();
        context = cordova.getContext();
        threadPool = cordova.getThreadPool();
        LOG.i(TAG, "Plugin initialize success");
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
        } else if (MethodNames.GEO_FENCE_IN.equalsIgnoreCase(action)) {
            PluginResult result = new PluginResult(PluginResult.Status.NO_RESULT);
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);
            geoFenceIn(callbackContext, args);
        } else if (MethodNames.GEO_FENCE_OUT.equalsIgnoreCase(action)) {
            PluginResult result = new PluginResult(PluginResult.Status.NO_RESULT);
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);
            geoFenceOut(callbackContext, args);
        } else if (MethodNames.GEO_FENCE_STAYED.equalsIgnoreCase(action)) {
            PluginResult result = new PluginResult(PluginResult.Status.NO_RESULT);
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);
            geoFenceStayed(callbackContext, args);
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
        String GEO_FENCE_IN = "geoFenceIn";
        String GEO_FENCE_OUT = "geoFenceOut";
        String GEO_FENCE_STAYED = "geoFenceStayed";
    }

    public interface GeoFenceCallBackType {
        String ADD_SUCCESS = "ADD_SUCCESS";
        String ADD_ERROR = "ADD_ERROR";
        String GEO_FENCE_IN = "GEO_FENCE_IN";
        String GEO_FENCE_OUT = "GEO_FENCE_OUT";
        String GEO_FENCE_STAYED = "GEO_FENCE_STAYED";
    }

    private void getLocation(CallbackContext callbackContext, JSONArray args) {
        AMapLocationClient aMapLocationClient = new AMapLocationClient(context);
        aMapLocationClient.setLocationListener(new AMapLocationListener(callbackContext, aMapLocationClient));
        AMapLocationClientOption aMapLocationClientOption = new AMapLocationClientOption().setLocationPurpose(AMapLocationClientOption.AMapLocationPurpose.SignIn);
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
        DPoint startPoint = new DPoint();
        try {
            startPoint.setLatitude(args.getLong(0));
            startPoint.setLongitude(args.getLong(1));
            DPoint endPoint = new DPoint();
            endPoint.setLatitude(args.getLong(2));
            endPoint.setLongitude(args.getLong(3));
            float v = CoordinateConverter.calculateLineDistance(startPoint, endPoint);
            callbackContext.success(String.valueOf(v));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private void geoFenceIn(CallbackContext callbackContext, JSONArray args) {
        if (geoFenceInClient != null) {
            geoFenceInClient.removeGeoFence();
        } else {
            geoFenceInClient = new GeoFenceClient(context);
        }
        geoFenceInClient.setActivateAction(GeoFenceClient.GEOFENCE_IN);
        createGeoFence(callbackContext, args, geoFenceInClient);
    }

    private void geoFenceOut(CallbackContext callbackContext, JSONArray args) {
        if (geoFenceOutClient != null) {
            geoFenceOutClient.removeGeoFence();
        } else {
            geoFenceOutClient = new GeoFenceClient(context);
        }
        geoFenceOutClient.setActivateAction(GeoFenceClient.GEOFENCE_OUT);
        createGeoFence(callbackContext, args, geoFenceOutClient);
    }

    private void geoFenceStayed(CallbackContext callbackContext, JSONArray args) {
        if (geoFenceStayedClient != null) {
            geoFenceStayedClient.removeGeoFence();
        } else {
            geoFenceStayedClient = new GeoFenceClient(context);
        }
        geoFenceStayedClient.setActivateAction(GeoFenceClient.GEOFENCE_STAYED);
        createGeoFence(callbackContext, args, geoFenceStayedClient);
    }

    private void createGeoFence(CallbackContext callbackContext, JSONArray args, GeoFenceClient geoFenceClient) {
        DPoint centerPoint = new DPoint();
        try {
            centerPoint.setLatitude(args.getDouble(0));
            centerPoint.setLongitude(args.getDouble(1));
            geoFenceClient.addGeoFence(centerPoint, args.getInt(0), "");
            geoFenceClient.setGeoFenceListener(new AMapGenFenceListener(callbackContext));
            geoFenceClient.createPendingIntent(GEO_FENCE_BROADCAST_ACTION);
            IntentFilter filter = new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION);
            filter.addAction(GEO_FENCE_BROADCAST_ACTION);
            context.registerReceiver(new AMapGeoFenceReceiver(callbackContext), filter);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
}
