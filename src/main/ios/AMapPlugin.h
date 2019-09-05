#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Cordova/CDV.h>
#import <AMapFoundationKit/AMapFoundationKit.h>
#import <AMapLocationKit/AMapLocationKit.h>
#import <AMapSearchKit/AMapSearchKit.h>
#import <MAMapKit/MAGeometry.h>
@interface AMapPlugin : AMapPluginSearchAPI{

    //NSString* callbackId;
}
@property (nonatomic, strong) AMapSearchAPI *search;
@property (nonatomic, strong) NSString *callbackId;
@property (nonatomic, strong) NSString *appKeyConfig;
@property (nonatomic, strong) AMapLocationManager *locationManager;
@property (nonatomic, copy) AMapLocatingCompletionBlock completionBlock;
@property (nonatomic, strong) NSString *appendAddress;


- (void)getLocation:(CDVInvokedUrlCommand*)command;
- (void)calculateDistance:(CDVInvokedUrlCommand*)command;
- (void)getWeatherInfo:(CDVInvokedUrlCommand*)command;
@end
