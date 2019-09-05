package com.chenwei116057.plugin;

import com.amap.api.fence.GeoFence;
import com.amap.api.fence.GeoFenceListener;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.LOG;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

public class AMapGenFenceListener implements GeoFenceListener {
    private CallbackContext callbackContext;
    private static final String TAG = "AMapPlugin";

    @Override
    public void onGeoFenceCreateFinished(List<GeoFence> geoFenceList, int code, String customId) {
        JSONObject object = new JSONObject();
        if (code == GeoFence.ADDGEOFENCE_SUCCESS) {//判断围栏是否创建成功
            LOG.i(TAG, "添加地理围栏成功");
            try {
                object.put("type", AMapPlugin.GeoFenceCallBackType.ADD_SUCCESS);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(object);
        } else {
            LOG.e(TAG, "添加地理围栏失败");
            try {
                object.put("type", AMapPlugin.GeoFenceCallBackType.ADD_ERROR);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.error(object);
        }
    }

    public AMapGenFenceListener(CallbackContext callbackContext) {
        this.callbackContext = callbackContext;
    }
}
