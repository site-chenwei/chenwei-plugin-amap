package com.chenwei.cordova.plugin;

import com.amap.api.services.weather.LocalWeatherForecastResult;
import com.amap.api.services.weather.LocalWeatherLive;
import com.amap.api.services.weather.LocalWeatherLiveResult;
import com.amap.api.services.weather.WeatherSearch;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.LOG;
import org.json.JSONException;
import org.json.JSONObject;

public class AMapWeatherSearchListener implements WeatherSearch.OnWeatherSearchListener {
    private CallbackContext callbackContext;
    private static final String TAG = "AMapPlugin";

    @Override
    public void onWeatherLiveSearched(LocalWeatherLiveResult result, int code) {
        if (code == 1000) {
            if (result != null && result.getLiveResult() != null) {
                JSONObject jsonObject = new JSONObject();
                LocalWeatherLive live = result.getLiveResult();
                try {
                    jsonObject.put("weather", live.getWeather());
                    jsonObject.put("temperature", live.getTemperature());
                    jsonObject.put("city", live.getCity());
                    jsonObject.put("province", live.getProvince());
                    jsonObject.put("windDirection", live.getWindDirection());
                    jsonObject.put("windPower", live.getWindPower());
                    jsonObject.put("humidity", live.getHumidity());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackContext.success(jsonObject);
            } else {
                LOG.e(TAG, "获取天气失败");
                callbackContext.error("获取天气失败");
            }
        } else {
            LOG.e(TAG, "获取天气失败");
            callbackContext.error("获取天气失败");
        }
    }

    @Override
    public void onWeatherForecastSearched(LocalWeatherForecastResult localWeatherForecastResult, int i) {

    }

    public AMapWeatherSearchListener(CallbackContext callbackContext) {
        this.callbackContext = callbackContext;
    }
}
