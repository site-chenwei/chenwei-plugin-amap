//
//  MAOverlayRenderer.h
//  MAMapKit
//
//
//  Copyright (c) 2011年 Amap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MAOverlay.h"
#import "MALineDrawType.h"

#define kMAOverlayRendererDefaultStrokeColor [UIColor colorWithRed:0.3 green:0.63 blue:0.89 alpha:0.8]
#define kMAOverlayRendererDefaultFillColor [UIColor colorWithRed:0.77 green:0.88 blue:0.94 alpha:0.8]

@protocol MAOverlayRenderDelegate;

///该类是地图覆盖物Renderer的基类
@interface MAOverlayRenderer : NSObject

///由地图添加时，不要手动设置。如果不是使用map进行添加，则需要手动设置。
@property (nonatomic, weak) id<MAOverlayRenderDelegate> rendererDelegate;

///z值，大值在上，默认为1。覆盖物的叠加顺序。默认叠加顺序，先添加的在底层，后添加的在上层。默认为10
@property (nonatomic, assign) NSInteger zIndex;

///关联的overlay对象
@property (nonatomic, readonly, retain) id <MAOverlay> overlay;

///透明度[0，1]，默认为1。
@property (nonatomic, assign) CGFloat alpha;

///是否可见，默认为YES
@property (nonatomic, assign) BOOL isVisible;

/**
 * @brief 初始化并返回一个Overlay Renderer
 * @param overlay 关联的overlay对象
 * @return 初始化成功则返回overlay view,否则返回nil
 */
- (instancetype)initWithOverlay:(id<MAOverlay>)overlay;

/**
 * @brief 当关联overlay对象有更新时，调用此接口刷新.
 */
- (void)setNeedsUpdate;

@end
