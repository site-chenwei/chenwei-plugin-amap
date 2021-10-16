//
//  MAOverlayRenderer.h
//  MAMapKit
//
//
//  Copyright (c) 2011年 Amap. All rights reserved.
//

#import "MAConfig.h"
#import <UIKit/UIKit.h>
#import "MAOverlay.h"
#import "MALineDrawType.h"

#define kMAOverlayRendererDefaultStrokeColor [UIColor colorWithRed:0.3 green:0.63 blue:0.89 alpha:0.8]
#define kMAOverlayRendererDefaultFillColor [UIColor colorWithRed:0.77 green:0.88 blue:0.94 alpha:0.8]

@protocol MAOverlayRenderDelegate,MTLRenderCommandEncoder;

///该类是地图覆盖物Renderer的基类, 提供绘制overlay的接口但并无实际的实现（render相关方法只能在重写后的glRender方法中使用）
@interface MAOverlayRenderer : NSObject {
    @protected
    GLuint _strokeTextureID;
    CGSize _strokeTextureSize;
    BOOL _needsUpdate;
    BOOL _needsLoadStrokeTexture;
}

///由地图添加时，不要手动设置。如果不是使用mapview进行添加，则需要手动设置。（since 5.1.0）
@property (nonatomic, weak) id<MAOverlayRenderDelegate> rendererDelegate;

///关联的overlay对象
@property (nonatomic, readonly, retain) id <MAOverlay> overlay;

///用于生成笔触纹理id的图片（支持非PowerOfTwo图片; 如果您需要减轻绘制产生的锯齿,您可以参考AMap.bundle中的traffic_texture_blue.png的方式,在image两边增加部分透明像素.)。（since 5.3.0）
@property (nonatomic, strong) UIImage *strokeImage;

///笔触纹理id, 修改纹理id参考, 如果strokeImage未指定、尚未加载或加载失败返回0. 注意：仅使用gles环境
@property (nonatomic, readonly) GLuint strokeTextureID __attribute((deprecated("已废弃，since 7.9.0")));

///透明度[0，1]，默认为1. 使用MAOverlayRenderer类提供的渲染接口会自动应用此属性。（since 5.1.0）
@property (nonatomic, assign) CGFloat alpha;

///overlay渲染的scale。（since 5.1.0）
@property (nonatomic, readonly) CGFloat contentScale;

/**
 * @brief 初始化并返回一个Overlay Renderer
 * @param overlay 关联的overlay对象
 * @return 初始化成功则返回overlay view,否则返回nil
 */
- (instancetype)initWithOverlay:(id<MAOverlay>)overlay;

/**
 *  @brief 获取当前地图view矩阵，数组长度为16，无需外界释放. 需要添加至地图后，才能获取有效矩阵数据，否则返回NULL
 *  @return 矩阵数组
 */
- (float *)getViewMatrix;

/**
 *  @brief 获取当前地图projection矩阵，数组长度为16，无需外界释放. 需要添加至地图后，才能获取有效矩阵数据，否则返回NULL
 *  @return 矩阵数组
 */
- (float *)getProjectionMatrix;

/**
 *  @brief 获取当前地图中心点偏移，用以把地图坐标转换为gl坐标。需要添加到地图获取才有效。（since 5.1.0）
 *  @return 偏移
 */
- (MAMapPoint)getOffsetPoint;

/**
 *  @brief 获取Metal渲染MTLRenderCommandEncoder对象。注意：打开地图MetalEnable时有效，否则为nil（since 7.9.0）
 *  @return 偏移
 */
- (id<MTLRenderCommandEncoder>)getCommandEncoder;

/**
 *  @brief 获取当前地图缩放级别，需要添加到地图获取才有效。（since 5.1.0）
 *  @return 缩放级别
 */
- (CGFloat)getMapZoomLevel;

/**
 * @brief 将MAMapPoint转换为opengles可以直接使用的坐标
 * @param mapPoint MAMapPoint坐标
 * @return 直接支持的坐标
 */
- (CGPoint)glPointForMapPoint:(MAMapPoint)mapPoint;

/**
 * @brief 批量将MAMapPoint转换为opengles可以直接使用的坐标
 * @param mapPoints MAMapPoint坐标数据指针
 * @param count     个数
 * @return 直接支持的坐标数据指针(需要调用者手动释放)
 */
- (CGPoint *)glPointsForMapPoints:(MAMapPoint *)mapPoints count:(NSUInteger)count;

/**
 * @brief 将屏幕尺寸转换为OpenGLES尺寸
 * @param windowWidth 屏幕尺寸
 * @return OpenGLES尺寸
 */
- (CGFloat)glWidthForWindowWidth:(CGFloat)windowWidth;

/**
 * @brief 绘制函数(子类需要重载来实现)
 */
- (void)glRender;

/**
 * @brief 加载纹理图片. 注意：仅使用gles环境（since 5.1.0）
 * @param textureImage 纹理图片（需满足：长宽相等，且宽度值为2的次幂)
 * @return openGL纹理ID, 若纹理加载失败返回0
 */
- (GLuint)loadTexture:(UIImage *)textureImage __attribute((deprecated("已废弃，since 7.9.0")));

/**
 @brief 删除纹理.  注意：仅使用gles环境（since 5.1.0）
 @param textureId 纹理ID
 */
- (void)deleteTexture:(GLuint)textureId __attribute((deprecated("已废弃，since 7.9.0")));

/**
 * @brief 当关联overlay对象有更新时，调用此接口刷新. since 5.0.0
 */
- (void)setNeedsUpdate;

@end
