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
    }
};
module.exports = AMapPlugin;
