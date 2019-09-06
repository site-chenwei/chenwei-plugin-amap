# chenwei-plugin-amap
使用高德Android定位SDK进行定位，以解决webapp中定位不准的问题

## 安装
`ionic cordova plugin add chenwei-plugin-amap --variable ANDROID_KEY=your android key --variable IOS_KEY=your ios key
npm i @chenwei116057/amap` `
## 使用
    在app.module.ts引入AMapPlugin
    
    
    import {AMapPlugin} from '@chenwei116057/amap';
    ...
    providers: [
        AMapPlugin
    ]
## 方法介绍
### 获取当前位置信息(IOS/安卓)
`getLocation(): Promise<LocationResult|void>;
`
`LocationResult {
    /**
     * 定位精度 仅android存在，IOS恒为undefined
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
     * 定位时间 仅android存在，IOS恒为undefined
     */
    locationTime: Date
}
`
### 获取天气信息(IOS/安卓)
`getWeatherInfo(params: { adCode: string }): Promise<WeatherInfo | void>;`
`WeatherInfo {
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
}`
### 计算两个坐标间的距离(IOS/安卓)
`calculateDistance(params: { startLatitude: number, startLongitude: number, endLatitude: number, endLongitude: number }): Promise<number | void>;`

    
