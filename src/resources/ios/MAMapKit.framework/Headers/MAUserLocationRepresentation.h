//
//  MAUserLocationRepresentation.h
//  MAMapKit
//
//  Created by shaobin on 16/12/27.
//  Copyright © 2016年 Amap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define kAccuracyCircleDefaultColor [UIColor colorWithRed:136/255.0 green:166/255.0 blue:227/255.0 alpha:.3]

///用户位置显示样式控制
@interface MAUserLocationRepresentation : NSObject

///精度圈是否显示，默认YES
@property (nonatomic, assign) BOOL showsAccuracyRing;
///精度圈 填充颜色, 默认 kAccuracyCircleDefaultColor
@property (nonatomic, strong) UIColor *fillColor;
///精度圈 边线颜色, 默认 kAccuracyCircleDefaultColor
@property (nonatomic, strong) UIColor *strokeColor;
///精度圈 边线宽度，默认0
@property (nonatomic, assign) CGFloat lineWidth;

///定位图标
@property (nonatomic, strong) UIImage* image;

@end
