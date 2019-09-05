package com.chenwei116057.plugin;


import com.amap.api.location.AMapLocation;
import com.amap.api.location.AMapLocationClient;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.LOG;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.Date;

public class AMapLocationListener implements com.amap.api.location.AMapLocationListener {
    private static final String TAG = "AMapPlugin";
    private CallbackContext callbackContext;
    private AMapLocationClient aMapLocationClient;

    @Override
    public void onLocationChanged(AMapLocation aMapLocation) {
        if (aMapLocation != null && 0 == aMapLocation.getErrorCode()) {
            LOG.i(TAG, "Location Success");
            JSONObject jsonObject = new JSONObject();
            try {
                jsonObject.put("accuracy", aMapLocation.getAccuracy());
                jsonObject.put("addressCode", aMapLocation.getAdCode());
                jsonObject.put("address", aMapLocation.getAddress());
                jsonObject.put("city", aMapLocation.getCity());
                jsonObject.put("cityCode", aMapLocation.getCityCode());
                jsonObject.put("altitude", aMapLocation.getAltitude());
                jsonObject.put("latitude", aMapLocation.getLatitude());
                jsonObject.put("longitude", aMapLocation.getLongitude());
                jsonObject.put("aoiName", aMapLocation.getAoiName());
                jsonObject.put("country", aMapLocation.getCountry());
                jsonObject.put("district", aMapLocation.getDistrict());
                jsonObject.put("poiName", aMapLocation.getPoiName());
                jsonObject.put("province", aMapLocation.getProvince());
                jsonObject.put("street", aMapLocation.getStreet());
                jsonObject.put("streetNum", aMapLocation.getStreetNum());
                jsonObject.put("locationTime", new Date());
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(jsonObject);
        } else if (aMapLocation != null) {
            LOG.e(TAG, "Location Error, ErrCode:" + aMapLocation.getErrorCode() + ", errInfo:" + aMapLocation.getErrorInfo());
            callbackContext.error("Location Error, ErrCode:" + aMapLocation.getErrorCode() + ", errInfo:" + aMapLocation.getErrorInfo());
        } else {
            LOG.e(TAG, "Location Error, No Error Message");
            callbackContext.error("Location Error, No Error Message");
        }
        aMapLocationClient.stopLocation();
    }

    public AMapLocationListener(CallbackContext callbackContext, AMapLocationClient aMapLocationClient) {
        this.callbackContext = callbackContext;
        this.aMapLocationClient = aMapLocationClient;
    }
}
