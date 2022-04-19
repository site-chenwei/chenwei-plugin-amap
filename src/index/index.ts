import {cordova, IonicNativePlugin} from '@ionic-native/core';
import {Observable} from "rxjs";
import {Injectable} from "@angular/core";

@Injectable({
    providedIn: 'root'
})
export class AMapPlugin extends IonicNativePlugin {
    constructor() {
        super();
        AMapPlugin.pluginName = "AMapPlugin";
        AMapPlugin.plugin = "cordova-plugin-amap";
        AMapPlugin.pluginRef = "AMapPlugin";
        AMapPlugin.repo = "https://github.com/site-chenwei/chenwei-plugin-amap";
        AMapPlugin.platforms = ["Android", "iOS"];
    }

    getLocation(): Promise<LocationResult | void> {
        return cordova(this, "getLocation", {}, arguments);
    };

    getWeatherInfo(params: { adCode: string }): Promise<WeatherInfo | void> {
        return cordova(this, "getWeatherInfo", {}, arguments);
    };

    calculateDistance(params: { startLatitude: number, startLongitude: number, endLatitude: number, endLongitude: number }): Promise<number | void> {
        return cordova(this, "calculateDistance", {}, arguments);
    };

    addGeofence(params: { latitude: number, longitude: number, length: number, customId: string }): Promise<number | void> {
        return cordova(this, "addGeofence", {}, arguments);
    };

    onGeofenceResult(): Observable<GeoFenceResult | void> {
        return cordova(this, "onGeofenceResult", {observable: true}, arguments);
    };
}

export interface LocationResult {
    /**
     * 定位精度
     */
    accuracy: number;
    /**
     * 区域编码
     */
    adCode: string;
    /**
     * 地址
     */
    address: string;
    /**
     * 城市|区
     */
    city: string;
    /**
     * 城市编码
     */
    cityCode: string;
    /**
     *精度
     */
    latitude: number;
    /**
     *纬度
     */
    longitude: number;
    /**
     * 当前定位点的AOI信息
     */
    aoiName: string;
    /**
     * 国家
     */
    country: string;
    /**
     * 城区信息
     */
    district: string;
    /**
     * 当前定位点的POI信息
     */
    poiName: string;
    /**
     * 省份
     */
    province: string;
    /**
     * 街道
     */
    street: string;
    /**
     * 街道号
     */
    streetNum: string;
    /**
     * 定位时间
     */
    locationTime: Date
}

export interface GeoFenceResult {
    /**
     * 状态，1:进入围栏区域 2:离开围栏区域 4：停留在围栏区域
     */
    status: number;
    /**
     * 业务GeoFenceId
     */
    customId: string;
}

export interface WeatherInfo {
    type: "live" | "forecast";
    /**
     * 天气
     */
    weather: string;
    /**
     * 温度
     */
    temperature: string;
    /**
     * 城市|区
     */
    city: string;
    /**
     * 省份
     *
     */
    province: string;
    /**
     * 风向
     */
    windDirection: string;
    /**
     * 风力
     */
    windPower: string;
    /**
     * 湿度
     */
    humidity: string;
}
