package com.chenwei116057.plugin;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import com.amap.api.fence.GeoFence;
import com.amap.api.fence.GeoFenceListener;

import org.apache.cordova.CallbackContext;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AMapGeofenceListener extends BroadcastReceiver implements GeoFenceListener {
    private static final Map<String, CallbackContext> CREATE_CONTEXT = new HashMap<>();
    private static final List<CallbackContext> RECEIVE_CONTEXT = new ArrayList<>();

    @Override
    public void onReceive(Context context, Intent intent) {
        Bundle bundle = intent.getExtras();
        int status = bundle.getInt(GeoFence.BUNDLE_KEY_FENCESTATUS);
        String customId = bundle.getString(GeoFence.BUNDLE_KEY_CUSTOMID);
        JSONObject jsonObject = new JSONObject();
        if (customId != null) {
            try {
                jsonObject.put("customId", customId);
                jsonObject.put("status", status);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            for (CallbackContext receiveContext : RECEIVE_CONTEXT) {
                receiveContext.success(jsonObject);
            }
        }
    }

    @Override
    public void onGeoFenceCreateFinished(List<GeoFence> list, int status, String customId) {
        CallbackContext callbackContext = CREATE_CONTEXT.get(customId);
        if (callbackContext != null) {
            callbackContext.success(status == GeoFence.ADDGEOFENCE_SUCCESS ? "success" : "error");
            CREATE_CONTEXT.remove(customId);
        }
    }

    public void onCreate(CallbackContext callbackContext, String customId) {
        CREATE_CONTEXT.put(customId, callbackContext);
    }

    public void onReceive(CallbackContext callbackContext) {
        RECEIVE_CONTEXT.add(callbackContext);
    }
}
