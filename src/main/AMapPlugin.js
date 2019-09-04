var exec = require('cordova.exec');

var AMapPlugin = {
    getLocation: (success, fail) => {
        exec(success, fail, 'AMapPlugin', 'getLocation', []);
    },
    getWeatherInfo: (params, success, fail) => {
        exec(success, fail, 'AMapPlugin', 'getWeatherInfo', [params]);
    },
    calculateDistance: (params, success, fail) => {
        exec(success, fail, 'AMapPlugin', 'calculateDistance', [params]);
    },
    geoFenceIn: (params, success, fail) => {
        exec(success, fail, 'AMapPlugin', 'geoFenceIn', [params]);
    },
    geoFenceOut: (params, success, fail) => {
        exec(success, fail, 'AMapPlugin', 'geoFenceOut', [params]);
    },
    geoFenceStayed: (params, success, fail) => {
        exec(success, fail, 'AMapPlugin', 'geoFenceStayed', [params]);
    }
};
module.exports = AMapPlugin;
