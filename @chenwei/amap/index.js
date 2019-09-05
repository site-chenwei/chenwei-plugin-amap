var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({__proto__: []} instanceof Array && function (d, b) {
                d.__proto__ = b;
            }) ||
            function (d, b) {
                for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
            };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);

        function __() {
            this.constructor = d;
        }

        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length,
        r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
/**
 * This is a template for new plugin wrappers
 *
 * TODO:
 * - Add/Change information below
 * - Document usage (importing, executing main functionality)
 * - Remove any imports that you are not using
 * - Remove all the comments included in this template, EXCEPT the @Plugin wrapper docs and any other docs you added
 * - Remove this note
 *
 */
import {Injectable} from '@angular/core';
import {cordova, IonicNativePlugin} from '@ionic-native/core';

var AMapPlugin = /** @class */ (function (_super) {
    __extends(AMapPlugin, _super);

    function AMapPlugin() {
        return _super !== null && _super.apply(this, arguments) || this;
    }

    AMapPlugin.prototype.functionName = function (arg1, arg2) {
        return cordova(this, "functionName", {}, arguments);
    };
    AMapPlugin.prototype.getLocation = function () {
        return cordova(this, "getLocation", {}, arguments);
    };
    AMapPlugin.prototype.getWeatherInfo = function (params) {
        return cordova(this, "getWeatherInfo", {}, arguments);
    };
    AMapPlugin.prototype.calculateDistance = function (params) {
        return cordova(this, "calculateDistance", {}, arguments);
    };
    AMapPlugin.prototype.geoFenceIn = function (params) {
        return cordova(this, "geoFenceIn", {}, arguments);
    };
    AMapPlugin.prototype.geoFenceOut = function (params) {
        return cordova(this, "geoFenceOut", {}, arguments);
    };
    AMapPlugin.prototype.geoFenceStayed = function (params) {
        return cordova(this, "geoFenceStayed", {}, arguments);
    };
    AMapPlugin.pluginName = "AMapPlugin";
    AMapPlugin.plugin = "cordova-plugin-amap";
    AMapPlugin.pluginRef = "plugins.AMapPlugin";
    AMapPlugin.repo = "https://github.com/chenwei116057/cordova-plugin-amap";
    AMapPlugin.install = "ionic cordova plugin add https://github.com/chenwei116057/cordova-plugin-amap.git --variable ANDROID_KEY=your_android_key --variable IOS_KEY=your_ios_key ";
    AMapPlugin.installVariables = ["ANDROID_KEY", "IOS_KEY"];
    AMapPlugin.platforms = ["Android", "iOS"];
    AMapPlugin = __decorate([
        Injectable({
            providedIn: 'root'
        })
    ], AMapPlugin);
    return AMapPlugin;
}(IonicNativePlugin));
export {AMapPlugin};
