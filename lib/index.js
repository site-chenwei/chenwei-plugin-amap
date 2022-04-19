"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var AMapPlugin_1;
Object.defineProperty(exports, "__esModule", { value: true });
exports.AMapPlugin = void 0;
const core_1 = require("@ionic-native/core");
const core_2 = require("@angular/core");
let AMapPlugin = AMapPlugin_1 = class AMapPlugin extends core_1.IonicNativePlugin {
    constructor() {
        super();
        AMapPlugin_1.pluginName = "AMapPlugin";
        AMapPlugin_1.plugin = "cordova-plugin-amap";
        AMapPlugin_1.pluginRef = "AMapPlugin";
        AMapPlugin_1.repo = "https://github.com/site-chenwei/chenwei-plugin-amap";
        AMapPlugin_1.platforms = ["Android", "iOS"];
    }
    getLocation() {
        return (0, core_1.cordova)(this, "getLocation", {}, arguments);
    }
    ;
    getWeatherInfo(params) {
        return (0, core_1.cordova)(this, "getWeatherInfo", {}, arguments);
    }
    ;
    calculateDistance(params) {
        return (0, core_1.cordova)(this, "calculateDistance", {}, arguments);
    }
    ;
    addGeofence(params) {
        return (0, core_1.cordova)(this, "addGeofence", {}, arguments);
    }
    ;
    onGeofenceResult() {
        return (0, core_1.cordova)(this, "onGeofenceResult", { observable: true }, arguments);
    }
    ;
};
AMapPlugin = AMapPlugin_1 = __decorate([
    (0, core_2.Injectable)({
        providedIn: 'root'
    })
], AMapPlugin);
exports.AMapPlugin = AMapPlugin;
//# sourceMappingURL=index.js.map