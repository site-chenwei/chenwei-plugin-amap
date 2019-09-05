var exec = require('cordova.exec');

function AMapPlugin() {

}

AMapPlugin.prototype.getLocation = function (success, fail) {
    exec(success, fail, 'AMapPlugin', 'getLocation', []);
}
AMapPlugin.prototype.getWeatherInfo = function (params, success, fail) {
    exec(success, fail, 'AMapPlugin', 'getWeatherInfo', [params]);
}
AMapPlugin.prototype.calculateDistance = function (params, success, fail) {
    exec(success, fail, 'AMapPlugin', 'calculateDistance', [params.startLatitude, params.startLongitude, params.endLatitude, params.endLongitude]);
}
AMapPlugin.prototype.geoFenceIn = function (params, success, fail) {
    exec(success, fail, 'AMapPlugin', 'geoFenceIn', [params]);
}
AMapPlugin.prototype.geoFenceOut = function (params, success, fail) {
    exec(success, fail, 'AMapPlugin', 'geoFenceOut', [params]);
}
AMapPlugin.prototype.geoFenceStayed = function (params, success, fail) {
    exec(success, fail, 'AMapPlugin', 'geoFenceStayed', [params]);
}
module.exports = new AMapPlugin();
