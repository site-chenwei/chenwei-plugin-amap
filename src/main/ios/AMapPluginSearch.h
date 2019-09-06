#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Cordova/CDV.h>
#import <AMapFoundationKit/AMapFoundationKit.h>
#import <AMapLocationKit/AMapLocationKit.h>
#import <AMapSearchKit/AMapSearchKit.h>
#import <MAMapKit/MAGeometry.h>
#import "AMapPlugin.h"
@interface AMapPluginSearchAPI : CDVPlugin <AMapSearchDelegate>{}
@property (nonatomic, strong) NSString *appKeyConfig;
@property (nonatomic, strong) AMapSearchAPI *search;
@property (nonatomic, strong) AMapPlugin *plugin;

- (void)getWeatherInfo:(AMapPlugin*)plugin;

@end
