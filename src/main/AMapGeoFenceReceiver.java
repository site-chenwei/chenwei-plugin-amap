package com.chenwei116057.cordova.plugin;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import com.amap.api.fence.GeoFence;

import org.apache.cordova.CallbackContext;

public class AMapGeoFenceReceiver extends BroadcastReceiver {
    private CallbackContext callbackContext;
    private static final String TAG = "AMapPlugin";

    @Override
    public void onReceive(Context context, Intent intent) {
        Bundle bundle = intent.getExtras();
//获取围栏行为：
        int status = bundle.getInt(GeoFence.BUNDLE_KEY_FENCESTATUS);
//获取自定义的围栏标识：
        String customId = bundle.getString(GeoFence.BUNDLE_KEY_CUSTOMID);
//获取围栏ID:
        String fenceId = bundle.getString(GeoFence.BUNDLE_KEY_FENCEID);
//获取当前有触发的围栏对象：
        GeoFence fence = bundle.getParcelable(GeoFence.BUNDLE_KEY_FENCE);
    }

    public AMapGeoFenceReceiver(CallbackContext callbackContext) {
        this.callbackContext = callbackContext;
    }
}
