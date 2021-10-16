//
//  MAOfflineCity.h
//
//  Copyright (c) 2013年 Amap. All rights reserved.
//

#import "MAConfig.h"

#if MA_INCLUDE_OFFLINE

#import <Foundation/Foundation.h>
#import "MAOfflineItem.h"

///离线地图，城市信息
@interface MAOfflineCity : MAOfflineItem

///城市编码
@property (nonatomic, copy, readonly) NSString *cityCode;

@end

#endif
