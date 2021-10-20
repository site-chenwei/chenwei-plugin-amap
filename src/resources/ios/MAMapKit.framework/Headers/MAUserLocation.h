//
//  MAUserLocation.h
//  MAMapKit
//
//  Created by yin cai on 12-1-4.
//  Copyright © 2016 Amap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAAnimatedAnnotation.h"
#import <AMapFoundationKit/AMapUtility.h>

@class CLLocation;
@class CLHeading;

///定位信息类
@interface MAUserLocation : MAAnimatedAnnotation

///位置信息
@property (nonatomic, strong, readonly) CLLocation *location;

///heading信息
@property (nonatomic, strong) CLHeading *heading;

- (void)setLocation:(CLLocation *)location coordinateType:(AMapCoordinateType)type;

@end
