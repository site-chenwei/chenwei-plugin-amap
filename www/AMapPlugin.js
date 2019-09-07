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
AMapPlugin.prototype.showMap = function (params, success, fail) {
    cordova.exec(success, fail, 'AMapPlugin', 'showMap', []);
}
module.exports = new AMapPlugin();
