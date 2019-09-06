#import "AMapPluginSearch.h"
#import "AMapPlugin.h"
#define DefaultLocationTimeout 3
#define DefaultReGeocodeTimeout 3
static NSString* const LATITUDE_KEY = @"latitude";
static NSString* const LONGITUDE_KEY = @"longitude";
static NSString* const ADDRESS_KEY = @"address";
static NSString* const DISTRICT_KEY = @"district";
static NSString* const ADCODE_KEY = @"adCode";
static NSString* const ACCURACY_KEY = @"accuracy";
static NSString* const CITY_KEY = @"city";
static NSString* const CITY_CODE_KEY = @"cityCode";
static NSString* const AOI_NAME_KEY = @"aoiName";
static NSString* const COUNTRY_KEY = @"country";
static NSString* const POI_NAME_KEY = @"poiName";
static NSString* const PROVINCE_KEY = @"province";
static NSString* const STREET_KEY = @"street";
static NSString* const STREET_NUM_KEY = @"streetNum";
static NSString* const LOCATION_TIME_KEY = @"locationTime";
static NSString* const WEATHER_KEY = @"weather";
static NSString* const TEMPERATURE_KEY = @"temperature";
static NSString* const WIND_DIRECTION_KEY = @"windDirection";
static NSString* const WIND_POWER_KEY = @"windPower";
static NSString* const HUMIDITY_KEY = @"humidity";
static NSString* const TYPE_KEY = @"type";
@implementation AMapPluginSearchAPI
- (void)getWeatherInfo:(AMapPlugin*)plugin{
    self.plugin=plugin;
    [AMapServices sharedServices].apiKey = [self appKeyConfig];
    self.search = [[AMapSearchAPI alloc] init];
    self.search.delegate=self;
    AMapWeatherSearchRequest *request = [[AMapWeatherSearchRequest alloc] init];
    NSString *myarg1 = [plugin.arguments objectAtIndex:0];
    request.city = myarg1;
    request.type = AMapWeatherTypeLive;
    [self.search AMapWeatherSearch:request];
}
- (void)onWeatherSearchDone:(AMapWeatherSearchRequest *)request response:(AMapWeatherSearchResponse *)response
{
        if (response.lives.count == 0)
        {
            CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"获取天气失败"];
            [self.plugin.commandDelegate sendPluginResult:pluginResult callbackId:self.plugin.callbackId];
        }
        AMapLocalWeatherLive *liveWeather = [response.lives firstObject];
       CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:[NSDictionary dictionaryWithObjectsAndKeys:
                       liveWeather.weather,WEATHER_KEY,
                       liveWeather.temperature,TEMPERATURE_KEY,
                       liveWeather.city,CITY_KEY,
                       liveWeather.province,PROVINCE_KEY,
                       liveWeather.windDirection,WIND_DIRECTION_KEY,
                       liveWeather.windPower,WIND_POWER_KEY,
                       liveWeather.humidity,HUMIDITY_KEY,
                       nil]];
        [self.plugin.commandDelegate sendPluginResult:pluginResult callbackId:self.plugin.callbackId];

 }
- (void)AMapSearchRequest:(id)request didFailWithError:(NSError *)error
{
   CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"获取天气失败"];
   [self.plugin.commandDelegate sendPluginResult:pluginResult callbackId:self.plugin.callbackId];
}
- (NSString *)appKeyConfig {
  if(!_appKeyConfig){
      NSString *path = [[NSBundle mainBundle] pathForResource:@"Info" ofType:@"plist"];
      NSDictionary *dic = [[NSDictionary alloc] initWithContentsOfFile:path];
      _appKeyConfig = [dic valueForKey:@"GaoDeAppKey"];
   }
    return _appKeyConfig;
}
@end
