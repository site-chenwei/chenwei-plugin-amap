package com.chenwei116057.plugin;


import com.amap.api.location.AMapLocation;
import com.amap.api.location.AMapLocationClient;
import com.amap.api.services.core.LatLonPoint;
import com.amap.api.services.geocoder.GeocodeResult;
import com.amap.api.services.geocoder.GeocodeSearch;
import com.amap.api.services.geocoder.RegeocodeAddress;
import com.amap.api.services.geocoder.RegeocodeQuery;
import com.amap.api.services.geocoder.RegeocodeResult;

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
        int errorCode = aMapLocation.getErrorCode();
        if (0 == aMapLocation.getErrorCode()) {
            if (aMapLocation.getAddress() != null && "".equals(aMapLocation.getAddress())) {
                GeocodeSearch geocoderSearch = new GeocodeSearch(AMapPlugin.activity);
                //判断定位完成只给返回经纬度，却不返回定位详细地理信息时
                LatLonPoint point = new LatLonPoint(aMapLocation.getLatitude(), aMapLocation.getLongitude());
                RegeocodeQuery query = new RegeocodeQuery(point, 200, GeocodeSearch.AMAP);
                geocoderSearch.getFromLocationAsyn(query);
                geocoderSearch.setOnGeocodeSearchListener(new GeocodeSearch.OnGeocodeSearchListener() {
                    @Override
                    public void onRegeocodeSearched(RegeocodeResult regeocodeResult, int i) {
                        RegeocodeAddress regeocodeAddress = regeocodeResult.getRegeocodeAddress();
                        LOG.i(TAG, "Regeo Success");
                        JSONObject jsonObject = new JSONObject();
                        try {
                            jsonObject.put("adCode", regeocodeAddress.getAdCode());
                            jsonObject.put("address", regeocodeAddress.getFormatAddress());
                            jsonObject.put("city", regeocodeAddress.getCity());
                            jsonObject.put("cityCode", regeocodeAddress.getCityCode());
                            jsonObject.put("latitude", aMapLocation.getLatitude());
                            jsonObject.put("longitude", aMapLocation.getLongitude());
                            if (regeocodeAddress.getAois().size() > 0) {
                                jsonObject.put("aoiName", regeocodeAddress.getAois().get(0).getAoiName());
                            }
                            if (regeocodeAddress.getPois().size() > 0) {
                                jsonObject.put("poiName", regeocodeAddress.getPois().get(0).getTitle());
                            }
                            jsonObject.put("country", regeocodeAddress.getCountry());
                            jsonObject.put("district", regeocodeAddress.getDistrict());
                            jsonObject.put("province", regeocodeAddress.getProvince());
                            jsonObject.put("streetNum", regeocodeAddress.getStreetNumber());
                            jsonObject.put("locationTime", new Date());
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        callbackContext.success(jsonObject);
                    }

                    @Override
                    public void onGeocodeSearched(GeocodeResult geocodeResult, int i) {

                    }
                });
            } else {
                LOG.i(TAG, "Location Success");
                JSONObject jsonObject = new JSONObject();
                try {
                    jsonObject.put("accuracy", aMapLocation.getAccuracy());
                    jsonObject.put("adCode", aMapLocation.getAdCode());
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
            }
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
