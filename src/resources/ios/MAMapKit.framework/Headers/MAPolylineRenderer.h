//
//  MAPolylineRenderer.h
//  MAMapKit
//
//  
//  Copyright (c) 2011年 Amap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MAPolyline.h"
#import "MAOverlayPathRenderer.h"

///此类用于绘制MAPolyline,可以通过MAOverlayPathRenderer修改其fill和stroke attributes
@interface MAPolylineRenderer : MAOverlayPathRenderer

///z值，大值在上，默认为1。覆盖物的叠加顺序。默认叠加顺序，先添加的在底层，后添加的在上层。默认为50
@property (nonatomic, assign) NSInteger zIndex;

///关联的MAPolyline model
@property (nonatomic, readonly) MAPolyline *polyline;

/**
 * @brief 根据指定的MAPolyline生成一个多段线Renderer
 * @param polyline 指定MAPolyline
 * @return 新生成的多段线Renderer
 */
- (instancetype)initWithPolyline:(MAPolyline *)polyline;

@end
