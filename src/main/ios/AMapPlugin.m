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
@interface AMapPlugin() <AMapSearchDelegate>
@property (nonatomic, strong) NSString *callbackId;
@property (nonatomic, strong) NSString *appKeyConfig;
@property (nonatomic, strong) AMapSearchAPI *search;
@property (nullable, copy) NSArray<NSExpression *> *arguments;
@property (nonatomic, strong) AMapLocationManager *locationManager;
@property (nonatomic, copy) AMapLocatingCompletionBlock completionBlock;
@property (nonatomic, strong) NSString *appendAddress;


- (void)getLocation:(CDVInvokedUrlCommand*)command;
- (void)calculateDistance:(CDVInvokedUrlCommand*)command;
- (void)getWeatherInfo:(CDVInvokedUrlCommand*)command;
@end
@implementation AMapPlugin
- (NSString *)appKeyConfig {
  if(!_appKeyConfig){
      NSString *path = [[NSBundle mainBundle] pathForResource:@"Info" ofType:@"plist"];
      NSDictionary *dic = [[NSDictionary alloc] initWithContentsOfFile:path];
      _appKeyConfig = [dic valueForKey:@"GaoDeAppKey"];
   }
    return _appKeyConfig;
}
- (void)getWeatherInfo:(CDVInvokedUrlCommand*)command{
    self.search = [[AMapSearchAPI alloc] init];
    self.callbackId=command.callbackId;
    self.search.delegate = self;
    AMapWeatherSearchRequest *request = [[AMapWeatherSearchRequest alloc] init];
    NSString *myarg1 = [command.arguments objectAtIndex:0];
    request.city = myarg1;
    request.type = AMapWeatherTypeLive;
    [self.search AMapWeatherSearch:request];
}
- (void)onWeatherSearchDone:(AMapWeatherSearchRequest *)request response:(AMapWeatherSearchResponse *)response
{
    if (response.lives.count == 0)
     {
         CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"获取天气失败"];
         [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackId];
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
     [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackId];
}
- (void)AMapSearchRequest:(id)request didFailWithError:(NSError *)error
{
   CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"获取天气失败"];
   [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackId];
}
- (void)calculateDistance:(CDVInvokedUrlCommand*)command{
  __weak AMapPlugin *weakSelf = self;
    NSString *myarg1 = [command.arguments objectAtIndex:0];
    NSString *myarg2 = [command.arguments objectAtIndex:1];
    NSString *myarg3 = [command.arguments objectAtIndex:2];
    NSString *myarg4 = [command.arguments objectAtIndex:3];
  MAMapPoint point1 = MAMapPointForCoordinate(CLLocationCoordinate2DMake([myarg1 doubleValue],[myarg2 doubleValue]));
  MAMapPoint point2 = MAMapPointForCoordinate(CLLocationCoordinate2DMake([myarg3 doubleValue],[myarg4 doubleValue]));
  CLLocationDistance distance = MAMetersBetweenMapPoints(point1,point2);
  CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDouble:distance];
  [weakSelf.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}
- (void)getLocation:(CDVInvokedUrlCommand*)command{
    self.callbackId = command.callbackId;
    [AMapServices sharedServices].apiKey = [self appKeyConfig];
    [self initCompleteBlock];

     if(self.locationManager == nil){
        self.locationManager = [[AMapLocationManager alloc] init];
        [self.locationManager setDelegate:self];

        //设置期望定位精度
        [self.locationManager setDesiredAccuracy:kCLLocationAccuracyBest];
        //设置不允许系统暂停定位
        [self.locationManager setPausesLocationUpdatesAutomatically:NO];
        //设置允许在后台定位
        //[self.locationManager setAllowsBackgroundLocationUpdates:YES];
        //设置定位超时时间
        [self.locationManager setLocationTimeout:DefaultLocationTimeout];
        //设置逆地理超时时间
        [self.locationManager setReGeocodeTimeout:DefaultReGeocodeTimeout];
     }
    if(![CLLocationManager locationServicesEnabled]){
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"定位服务未打开"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        return;
    }

    //进行单次带逆地理定位请求
    [self.locationManager requestLocationWithReGeocode:YES completionBlock:self.completionBlock];

}

- (void)initCompleteBlock {
    __weak AMapPlugin *weakSelf = self;
    self.completionBlock = ^(CLLocation *location, AMapLocationReGeocode *regeocode, NSError *error)
    {
        if (error != nil && error.code == AMapLocationErrorLocateFailed)
        {
            //定位错误：此时location和regeocode没有返回值，不进行annotation的添加
            NSString *errorMsg = [NSString stringWithFormat:@"定位错误:{%ld - %@};", (long)error.code, error.localizedDescription];
            [weakSelf failWithCallbackID:weakSelf.callbackId withMessage:errorMsg];
            NSLog(@"定位错误:{%ld - %@};", (long)error.code, error.localizedDescription);
            return;
        }
        else if (error != nil
                 && (error.code == AMapLocationErrorReGeocodeFailed
                     || error.code == AMapLocationErrorTimeOut
                     || error.code == AMapLocationErrorCannotFindHost
                     || error.code == AMapLocationErrorBadURL
                     || error.code == AMapLocationErrorNotConnectedToInternet
                     || error.code == AMapLocationErrorCannotConnectToHost))
        {
            //逆地理错误：在带逆地理的单次定位中，逆地理过程可能发生错误，此时location有返回值，regeocode无返回值，进行annotation的添加
            NSString *errorMsg = [NSString stringWithFormat:@"逆地理错误:{%ld - %@};", (long)error.code, error.localizedDescription];
            [weakSelf failWithCallbackID:weakSelf.callbackId withMessage:errorMsg];
            NSLog(@"逆地理错误:{%ld - %@};", (long)error.code, error.localizedDescription);
        }
        else if (error != nil && error.code == AMapLocationErrorRiskOfFakeLocation)
        {
            //存在虚拟定位的风险：此时location和regeocode没有返回值，不进行annotation的添加
            NSString *errorMsg = [NSString stringWithFormat:@"存在虚拟定位的风险:{%ld - %@};", (long)error.code, error.localizedDescription];
            [weakSelf failWithCallbackID:weakSelf.callbackId withMessage:errorMsg];
            NSLog(@"存在虚拟定位的风险:{%ld - %@};", (long)error.code, error.localizedDescription);
            return;
        }
        else
        {
            //没有错误：location有返回值，regeocode是否有返回值取决于是否进行逆地理操作，进行annotation的添加
            if(weakSelf.callbackId != nil&& regeocode!=nil){
                NSString *address = [regeocode.province isEqualToString:regeocode.city] ?
                [NSString stringWithFormat:@"%@%@%@%@%@", regeocode.city, regeocode.district, regeocode.street, regeocode.number, regeocode.POIName] :
                [NSString stringWithFormat:@"%@%@%@%@%@%@", regeocode.province, regeocode.city, regeocode.district, regeocode.street, regeocode.number, regeocode.POIName];
                NSLog(@"地址信息：{%@}",address);
                CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:[NSDictionary dictionaryWithObjectsAndKeys:
                [NSNumber numberWithDouble: location.coordinate.longitude], LONGITUDE_KEY,
                [NSNumber numberWithDouble: location.coordinate.latitude], LATITUDE_KEY,
                address, ADDRESS_KEY,
                regeocode.number, STREET_NUM_KEY,
                regeocode.country, COUNTRY_KEY,
                regeocode.district,DISTRICT_KEY,
                regeocode.adcode,ADCODE_KEY,
                regeocode.province,PROVINCE_KEY,
                regeocode.street,STREET_KEY,
                regeocode.city,CITY_KEY,
                regeocode.citycode,CITY_CODE_KEY,
                regeocode.POIName,POI_NAME_KEY,
                regeocode.AOIName,AOI_NAME_KEY,
                nil]];
                [weakSelf.commandDelegate sendPluginResult:pluginResult callbackId:weakSelf.callbackId];
                weakSelf.callbackId = nil;
            }else{
            NSString *errorMsg = @"逆定理失败，无返回值";
                        [weakSelf failWithCallbackID:weakSelf.callbackId withMessage:errorMsg];
                        NSLog(@"逆定理失败，无返回值");
                        return;
            }
            [weakSelf.locationManager stopUpdatingLocation];
        }
    };
}

- (void)failWithCallbackID:(NSString *)callbackID withMessage:(NSString *)message {
    CDVPluginResult *commandResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:message];
    [self.commandDelegate sendPluginResult:commandResult callbackId:callbackID];
}

- (void)dealloc {
    //停止定位
    [self.locationManager stopUpdatingLocation];
    [self.locationManager setDelegate:nil];
    self.completionBlock = nil;
}


@end
