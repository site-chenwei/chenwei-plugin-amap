package com.chenwei.cordova.plugin;

import android.app.Activity;
import android.content.Context;

import com.amap.api.fence.GeoFence;
import com.amap.api.fence.GeoFenceClient;
import com.amap.api.location.AMapLocationClient;
import com.amap.api.location.AMapLocationClientOption;

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

    private void getLocation(CallbackContext callbackContext, JSONArray args) {
        AMapLocationClient aMapLocationClient = new AMapLocationClient(context);
        aMapLocationClient.setLocationListener(new AMapLocationListener(callbackContext, aMapLocationClient));
        AMapLocationClientOption aMapLocationClientOption = new AMapLocationClientOption().setLocationPurpose(AMapLocationClientOption.AMapLocationPurpose.SignIn);
        aMapLocationClient.setLocationOption(aMapLocationClientOption);
        aMapLocationClient.stopLocation();
        aMapLocationClient.startLocation();
    }

    private void getWeatherInfo(CallbackContext callbackContext, JSONArray args) {

    }

    private void calculateDistance(CallbackContext callbackContext, JSONArray args) {

    }

    private void geoFenceIn(CallbackContext callbackContext, JSONArray args) {
        GeoFenceClient geoFenceClient = new GeoFenceClient(context);
        geoFenceClient.setActivateAction(GeoFenceClient.GEOFENCE_IN);
    }

    private void geoFenceOut(CallbackContext callbackContext, JSONArray args) {
        GeoFenceClient geoFenceClient = new GeoFenceClient(context);
        geoFenceClient.setActivateAction(GeoFenceClient.GEOFENCE_OUT);
    }

    private void geoFenceStayed(CallbackContext callbackContext, JSONArray args) {
        GeoFenceClient geoFenceClient = new GeoFenceClient(context);
        geoFenceClient.setActivateAction(GeoFenceClient.GEOFENCE_STAYED);
    }

    private void createGeoFence(CallbackContext callbackContext, JSONArray args, GeoFenceClient geoFenceClient) {

    }
}
