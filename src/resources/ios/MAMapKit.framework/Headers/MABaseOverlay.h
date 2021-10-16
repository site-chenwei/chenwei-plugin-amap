//
//  MABaseOverlay.h
//  MAMapKit
//
//  Created by cuishaobin on 2020/6/17.
//  Copyright © 2020 Amap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAOverlay.h"

NS_ASSUME_NONNULL_BEGIN

@interface MABaseOverlay : NSObject<MAOverlay>

///返回区域中心坐标
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

///区域外接矩形
@property (nonatomic, assign) MAMapRect boundingMapRect;

@end

NS_ASSUME_NONNULL_END
