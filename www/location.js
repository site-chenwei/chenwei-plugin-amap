var cordova = require('cordova');

function AmapLocation(){}

AmapLocation.prototype.getLocation = function(successCallback,errorCallback) {
    cordova.exec(successCallback,errorCallback,"AmapLocation","getlocation",[]);
};
AmapLocation.prototype.getWeatherInfo = function(params,successCallback,errorCallback) {
    cordova.exec(successCallback,errorCallback,"AmapLocation","getWeatherInfo",[params.distinct]);
};
AmapLocation.prototype.calculateDistance = function(params, successCallback,errorCallback) {
  console.dir(params);
  cordova.exec(successCallback,errorCallback,"AmapLocation","calculatedistance",[params.lat1, params.lng1, params.lat2, params.lng2]);
};

module.exports = new AmapLocation();
