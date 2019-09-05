import {IonicNativePlugin} from '@ionic-native/core';

export declare class AMapPlugin extends IonicNativePlugin {
    /**
     * This function does something
     * @param arg1 {string} Some param to configure something
     * @param arg2 {number} Another param to configure something
     * @return {Promise<any>} Returns a promise that resolves when something happens
     */
    functionName(arg1: string, arg2: number): Promise<any>;

    getLocation(): Promise<LocationResult | void>;

    getWeatherInfo(params: { addressCode: string }): Promise<WeatherInfo | void>;

    calculateDistance(params: { startLatitude: number, startLongitude: number, endLatitude: number, endLongitude: number }): Promise<number | void>;

    geoFenceIn(params: { latitude: number, longitude: number, radius: number }): Promise<GeoFenceResult | void>;

    geoFenceOut(params: { latitude: number, longitude: number, radius: number }): Promise<GeoFenceResult | void>;

    geoFenceStayed(params: { latitude: number, longitude: number, radius: number }): Promise<GeoFenceResult | void>;
}

export interface LocationResult {

}

export interface WeatherInfo {

}

export interface GeoFenceResult {

}
