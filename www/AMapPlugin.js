function AMapPlugin() {

}

AMapPlugin.prototype.getLocation = function (success, fail) {
    cordova.exec(success, fail, 'AMapPlugin', 'getLocation', []);
}
AMapPlugin.prototype.getWeatherInfo = function (params, success, fail) {
    cordova.exec(success, fail, 'AMapPlugin', 'getWeatherInfo', [params.adCode]);
}
AMapPlugin.prototype.calculateDistance = function (params, success, fail) {
    cordova.exec(success, fail, 'AMapPlugin', 'calculateDistance', [params.startLatitude, params.startLongitude, params.endLatitude, params.endLongitude]);
}
AMapPlugin.prototype.onGeofenceResult = function (params, success, fail) {
    cordova.exec(success, fail, 'AMapPlugin', 'onGeofenceResult', []);
}
AMapPlugin.prototype.addGeofence = function (params, success, fail) {
    cordova.exec(success, fail, 'AMapPlugin', 'addGeofence', [params.latitude, params.longitude, params.length, params.customId]);
}
module.exports = new AMapPlugin();
