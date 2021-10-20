//
//  MAMap.h
//  MAMapKit
//
//  Created by 翁乐 on 3/17/16.
//  Copyright © 2020 Amap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MAOverlay.h"
#import "MAOverlayRenderer.h"
#import "MAAnnotation.h"
#import "MAAnnotationView.h"
#import "MACircle.h"
#import <AMapFoundationKit/AMapUtility.h>
#import "MAUserLocation.h"
#import "MAMapStatus.h"
#import "MAUserLocationRepresentation.h"
#import "MAMapCustomStyleOptions.h"
#import "MAPolylineRenderer.h"
#import "MAMapWebViewProcotol.h"
#import <WebKit/WebKit.h>
#import "MACustomSchemeModel.h"

///地图类型
typedef NS_ENUM(NSInteger, MAMapType)
{
    MAMapTypeStandard = 1,  ///< 普通地图
    MAMapTypeSatellite,     ///< 卫星地图
    MAMapTypeStandardNight  ///< 夜间视图
};

///用户跟踪模式
typedef NS_ENUM(NSInteger, MAUserTrackingMode)
{
    MAUserTrackingModeNone              = 0,    ///< 不追踪用户的location更新
    MAUserTrackingModeFollow            = 1,    ///< 追踪用户的location更新
    MAUserTrackingModeFollowWithHeading = 2     ///< 追踪用户的location与heading更新
};

#pragma mark - 动画相关的key

NS_ASSUME_NONNULL_BEGIN

@protocol MAMapDelegate;

@interface MAMap : NSObject

///地图的delegate
@property (nonatomic, weak) id<MAMapDelegate> delegate;

/////地图类型
@property (nonatomic) MAMapType mapType;

///当前地图的中心点，改变该值时，地图的比例尺级别不会发生变化
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;

///可见区域, 设定的该范围可能会被调整为适合地图窗口显示的范围
@property (nonatomic) MAMapRect visibleMapRect;

///设置可见地图区域的矩形边界，如限制地图只显示北京市范围
@property (nonatomic, assign) MACoordinateRegion limitRegion;
///设置可见地图区域的矩形边界，如限制地图只显示北京市范围
@property (nonatomic, assign) MAMapRect limitMapRect;

///缩放级别（默认3-20）
@property (nonatomic) CGFloat zoomLevel;
///最小缩放级别
@property (nonatomic) CGFloat minZoomLevel;
///最大缩放级别
@property (nonatomic) CGFloat maxZoomLevel;
///是否支持缩放, 默认YES
@property (nonatomic, getter = isZoomEnabled) BOOL zoomEnabled;

///设置地图旋转角度(逆时针为正向)
@property (nonatomic) CGFloat rotationDegree;
///是否支持旋转, 默认YES
@property (nonatomic, getter = isRotateEnabled) BOOL rotateEnabled;

///设置地图相机角度(范围为[0.f, 60.f]，但高于40度的角度需要在16级以上才能生效)
@property (nonatomic) CGFloat cameraDegree;
///是否支持camera旋转, 默认YES
@property (nonatomic, getter = isRotateCameraEnabled) BOOL rotateCameraEnabled;

///是否支持平移, 默认YES
@property (nonatomic, getter = isScrollEnabled) BOOL scrollEnabled;

///是否显示楼块，默认为YES
@property (nonatomic, getter = isShowsBuildings) BOOL showsBuildings;

///是否显示底图标注, 默认为YES
@property (nonatomic, assign, getter = isShowsLabels) BOOL showsLabels;

///是否显示交通路况图层, 默认为NO
@property (nonatomic, getter = isShowTraffic) BOOL showTraffic;

///标识当前地图中心位置是否在中国范围外。此属性不是精确判断，不能用于边界区域
@property (nonatomic, readonly) BOOL isAbroad;

///是否显示海外地图，默认为@NO. 注意：必须先在官网申请开通海外权限
@property (nonatomic, class, getter=isShowsWorldMap) BOOL showsWorldMap;

/**
 * @brief  获取需要注册的自定义
 * @return 返回webViewConfiguration用于初始化WKWebView
 */
+ (NSArray<MACustomSchemeModel*>*)customSchemeArray;

/**
 * @brief 使用外部webView初始化地图 (注意：该初始化方法不会加载地图，需要调用loadMap加载地图)
 * @param webView 外部创建的WKWebView (内部会强引用，此webView的configuration需要通过webViewConfiguration方法获取)
 */
- (instancetype)initWithWebView:(nonnull NSObject<MAMapWebViewProcotol>*)webView;

/**
 * @brief 加载地图
 */
- (void)createMap;

/**
 * @brief 设置可见区域
 * @param mapRect 要设定的可见区域
 * @param animated 是否动画设置
 */
- (void)setVisibleMapRect:(MAMapRect)mapRect animated:(BOOL)animated;

/**
 * @brief 设置可见地图矩形区域
 * @param insets 边缘插入
 * @param mapRect 要显示的地图矩形区域
 * @param animated 是否动画效果
 */
- (void)setVisibleMapRect:(MAMapRect)mapRect edgePadding:(UIEdgeInsets)insets animated:(BOOL)animated;

/**
 * @brief 设置当前地图的中心点，改变该值时，地图的比例尺级别不会发生变化
 * @param coordinate 要设置的中心点
 * @param animated 是否动画设置
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

/**
 * @brief 设置缩放级别
 * @param zoomLevel 要设置的缩放级别
 * @param animated 是否动画设置
 */
- (void)setZoomLevel:(CGFloat)zoomLevel animated:(BOOL)animated;

/**
 * @brief 设置旋转角度
 * @param rotationDegree 要设置的旋转角度
 * @param animated 是否动画设置
 */
- (void)setRotationDegree:(CGFloat)rotationDegree animated:(BOOL)animated;

/**
 * @brief 设置仰角角度
 * @param cameraDegree 要设置的仰角角度
 * @param animated 是否动画设置
 */
- (void)setCameraDegree:(CGFloat)cameraDegree animated:(BOOL)animated;

/**
 * @brief 获取地图状态
 * @return 地图状态
 */
- (MAMapStatus *)getMapStatus;

/**
 * @brief 设置地图状态
 * @param status 要设置的地图状态
 * @param animated 是否动画
 */
- (void)setMapStatus:(MAMapStatus *)status animated:(BOOL)animated;

/**
 * @brief 将经纬度转换为指定view坐标系的坐标
 * @param coordinate 经纬度
 * @param completeCallback 基于指定view坐标系的坐标
 */
- (void)convertCoordinate:(CLLocationCoordinate2D)coordinate completeCallback:(void(^)(CGPoint point))completeCallback;

/**
 * @brief 将指定view坐标系的坐标转换为经纬度
 * @param point 指定view坐标系的坐标
 * @param completeCallback 经纬度
 */
- (void)convertPoint:(CGPoint)point completeCallback:(void(^)(CLLocationCoordinate2D coordinate))completeCallback;

/**
 * @brief 获取地图审图号。如果启用了“自定义样式”功能(customMapStyleEnabled 为 YES)，则返回nil。
 * @return 地图审图号
 */
- (NSString *)mapContentApprovalNumber;

/**
 * @brief 获取卫星图片审图号。
 * @return 卫星图片审图号
 */
- (NSString *)satelliteImageApprovalNumber;

/**
 * @brief WKWebView长按事件透传。
 * @param gestureRecognizer 长按事件
 */
- (void)longPressGesture:(UILongPressGestureRecognizer *)gestureRecognizer;

@end

@interface MAMap (NetworkIntercept)

+ (void)startRequestWithURLProtocol:(NSURLProtocol*)urlProtocol;
+ (void)stopRequestWithURLProtocol:(NSURLProtocol*)urlProtocol;

@end

@interface MAMap (Annotation)

///所有添加的标注, 注意从5.3.0开始返回数组内不再包含定位蓝点userLocation
@property (nonatomic, readonly) NSArray *annotations;

///处于选中状态的标注数据数据(其count == 0 或 1)
@property (nonatomic, copy) NSArray *selectedAnnotations;

/**
 * @brief 向地图窗口添加标注，需要实现MAMapDelegate的-map:viewForAnnotation:函数来生成标注对应的View
 * @param annotation 要添加的标注
 */
- (void)addAnnotation:(id <MAAnnotation>)annotation;

/**
 * @brief 向地图窗口添加一组标注，需要实现MAMapDelegate的-map:viewForAnnotation:函数来生成标注对应的View
 * @param annotations 要添加的标注数组
 */
- (void)addAnnotations:(NSArray *)annotations;

/**
 * @brief 移除标注
 * @param annotation 要移除的标注
 */
- (void)removeAnnotation:(id <MAAnnotation>)annotation;

/**
 * @brief 移除一组标注
 * @param annotations 要移除的标注数组
 */
- (void)removeAnnotations:(NSArray *)annotations;

/**
 * @brief 根据标注数据获取标注view
 * @param annotation 标注数据
 * @return 对应的标注view
 */
- (MAAnnotationView *)viewForAnnotation:(id <MAAnnotation>)annotation;

/**
 * @brief 选中标注数据对应的view。注意：如果annotation对应的annotationView因不在屏幕范围内而被移入复用池，为了完成选中操作，会将对应的annotationView添加到地图上，并将地图中心点移至annotation.coordinate的位置。
 * @param annotation 标注数据
 * @param animated 是否有动画效果
 */
- (void)selectAnnotation:(id <MAAnnotation>)annotation animated:(BOOL)animated;

/**
 * @brief 取消选中标注数据对应的view
 * @param annotation 标注数据
 * @param animated 是否有动画效果
 */
- (void)deselectAnnotation:(id <MAAnnotation>)annotation animated:(BOOL)animated;

/**
 * @brief 设置地图使其可以显示数组中所有的annotation, 如果数组中只有一个则直接设置地图中心为annotation的位置。
 * @param annotations 需要显示的annotation
 * @param animated    是否执行动画
 */
- (void)showAnnotations:(NSArray *)annotations animated:(BOOL)animated;

/**
 * @brief 设置地图使其可以显示数组中所有的annotation, 如果数组中只有一个则直接设置地图中心为annotation的位置。
 * @param annotations 需要显示的annotation
 * @param insets      insets 嵌入边界
 * @param animated    是否执行动画
 */
- (void)showAnnotations:(NSArray *)annotations edgePadding:(UIEdgeInsets)insets animated:(BOOL)animated;

@end


@interface MAMap (UserLocation)

///是否显示用户位置，默认为NO
@property (nonatomic) BOOL showsUserLocation;

///当前的位置数据
@property (nonatomic, readonly) MAUserLocation *userLocation;

///是否自定义用户位置精度圈(userLocationAccuracyCircle)对应的 view, 默认为 NO.\n 如果为YES: 会调用 - (MAOverlayRenderer *)map (MAMap *)map rendererForOverlay:(id <MAOverlay>)overlay 若返回nil, 则不加载.\n 如果为NO : 会使用默认的样式.
@property (nonatomic) BOOL customizeUserLocationAccuracyCircleRepresentation;

///用户位置精度圈 对应的overlay
@property (nonatomic, readonly) MACircle *userLocationAccuracyCircle;

///定位用户位置的模式, 注意：在follow模式下，设置地图中心点、设置可见区域、滑动手势、选择annotation操作会取消follow模式，并触发 - (void)map:(MAMap *)map didChangeUserTrackingMode:(MAUserTrackingMode)mode animated:(BOOL)animated;
@property (nonatomic) MAUserTrackingMode userTrackingMode;

/**
 * @brief 设置当前用户位置，当showsUserLocation为YES时调用有效
 * @param location 当前用户定位location
 */
- (void)setUserLocation:(CLLocation*)location coordinateType:(AMapCoordinateType)type;

/**
 * @brief 设置当前用户设备方向，当showsUserLocation为YES时调用有效
 * @param heading 当前用户方向heading
 */
- (void)setUserHeading:(CLHeading*)heading;

/**
 * @brief 设置定位用户位置的模式
 * @param mode 要设置的模式
 * @param animated 是否动画设置
 */
- (void)setUserTrackingMode:(MAUserTrackingMode)mode animated:(BOOL)animated;

/**
 * @brief 设定UserLocationView样式。如果用户自定义了userlocation的annotationView，或者该annotationView还未添加到地图上，此方法将不起作用
 * @param representation 样式信息对象
 */
- (void)updateUserLocationRepresentation:(MAUserLocationRepresentation *)representation;

@end

@interface MAMap (Overlay)

///所有添加的Overlay
@property (nonatomic, readonly) NSArray *overlays;

/**
 * @brief 向地图窗口添加Overlay。
 * 需要实现MAMapDelegate的-map:rendererForOverlay:函数来生成标注对应的Renderer。
 * 默认添加层级：MAGroundOverlay默认层级为MAOverlayLevelAboveRoads，其余overlay类型默认层级为MAOverlayLevelAboveLabels
 * @param overlay 要添加的overlay
 */
- (void)addOverlay:(id <MAOverlay>)overlay;

/**
 * @brief 向地图窗口添加一组Overlay，需要实现MAMapDelegate的-map:rendererForOverlay:函数来生成标注对应的Renderer
 * 默认添加层级：MAOverlayLevelAboveLabels
 * @param overlays 要添加的overlay数组
 */
- (void)addOverlays:(NSArray *)overlays;

/**
 * @brief 移除Overlay
 * @param overlay 要移除的overlay
 */
- (void)removeOverlay:(id <MAOverlay>)overlay;

/**
 * @brief 移除一组Overlay
 * @param overlays 要移除的overlay数组
 */
- (void)removeOverlays:(NSArray *)overlays;

/**
 * @brief 查找指定overlay对应的Renderer，如果该View尚未创建，返回nil
 * @param overlay 指定的overlay
 * @return 指定overlay对应的Renderer
 */
- (MAOverlayRenderer *)rendererForOverlay:(id <MAOverlay>)overlay;

/**
 * @brief 设置地图使其可以显示数组中所有的overlay, 如果数组中只有一个则直接设置地图中心为overlay的位置。
 * @param overlays    需要显示的overlays
 * @param animated    是否执行动画
 */
- (void)showOverlays:(NSArray *)overlays animated:(BOOL)animated;

/**
 * @brief 设置地图使其可以显示数组中所有的overlay, 如果数组中只有一个则直接设置地图中心为overlay的位置。
 * @param overlays    需要显示的overlays
 * @param insets      insets 嵌入边界
 * @param animated    是否执行动画
 */
- (void)showOverlays:(NSArray *)overlays edgePadding:(UIEdgeInsets)insets animated:(BOOL)animated;

@end

#pragma mark - MAMapDelegate
@protocol MAMapDelegate <NSObject>

@optional

/**
 * @brief 地图初始化完成（在此之后，可以进行坐标计算）
 * @param map 地图
 */
- (void)mapReady:(MAMap *)map;

/**
 * @brief 地图区域改变过程中会调用此接口
 * @param map 地图
 */
- (void)mapRegionChanged:(MAMap *)map;

/**
 * @brief 地图区域改变完成后会调用此接口
 * @param map 地图
 */
- (void)mapRegionDidChanged:(MAMap *)map;

/**
 * @brief 根据anntation生成对应的View。
 注意：
 1、请不要在此回调中对annotation进行select和deselect操作，此时annotationView还未添加到map。
 * @param map 地图
 * @param annotation 指定的标注
 * @return 生成的标注View
 */
- (MAAnnotationView *)map:(MAMap *)map viewForAnnotation:(id <MAAnnotation>)annotation;

/**
 * @brief 单击annotation回调，返回annotationView
 * @param map 地图
 * @param annotationView annotationView对象
 */
- (void)map:(MAMap *)map didAnnotationViewTapped:(MAAnnotationView *)annotationView;

/**
 * @brief 当选中一个annotation view时，调用此接口. 注意如果已经是选中状态，再次点击不会触发此回调。取消选中需调用-(void)deselectAnnotation:animated:
 * @param map 地图
 * @param view 选中的annotation view
 */
- (void)map:(MAMap *)map didSelectAnnotationView:(MAAnnotationView *)view;

/**
 * @brief 当取消选中一个annotation view时，调用此接口
 * @param map 地图
 * @param view 取消选中的annotation view
 */
- (void)map:(MAMap *)map didDeselectAnnotationView:(MAAnnotationView *)view;

/**
 * @brief 拖动annotation view时view的状态变化
 * @param map 地图
 * @param view annotation view
 * @param newState 新状态
 * @param oldState 旧状态
 */
- (void)map:(MAMap *)map annotationView:(MAAnnotationView *)view didChangeDragState:(MAAnnotationViewDragState)newState
   fromOldState:(MAAnnotationViewDragState)oldState;

/**
 * @brief 根据overlay生成对应的Renderer
 * @param map 地图
 * @param overlay 指定的overlay
 * @return 生成的覆盖物Renderer
 */
- (MAOverlayRenderer *)map:(MAMap *)map rendererForOverlay:(id <MAOverlay>)overlay;

/**
 * @brief 当map新添加overlay renderers时，调用此接口
 * @param map 地图
 * @param overlayRenderers 新添加的overlay renderers
 */
- (void)map:(MAMap *)map didAddOverlayRenderers:(NSArray *)overlayRenderers;

/**
 * @brief 单击polyline回调，返回polylineRenderer
 * @param map 地图的view
 * @param polylineRenderer polylineRenderer
 */
- (void)map:(MAMap *)map didPolylineRendererTapped:(MAPolylineRenderer *)polylineRenderer;

/**
 * @brief 标注view的calloutview整体点击时，触发该回调。只有使用默认calloutview时才生效。
 * @param map 地图的view
 * @param view calloutView所属的annotationView
 */
- (void)map:(MAMap *)map didAnnotationViewCalloutTapped:(MAAnnotationView *)view;

/**
 * @brief 当userTrackingMode改变时，调用此接口
 * @param map 地图
 * @param mode 改变后的mode
 * @param animated 动画
 */
- (void)map:(MAMap *)map didChangeUserTrackingMode:(MAUserTrackingMode)mode animated:(BOOL)animated;

/**
 * @brief 单击地图回调，返回经纬度
 * @param map 地图View
 * @param coordinate 经纬度
 */
- (void)map:(MAMap *)map didSingleTappedAtCoordinate:(CLLocationCoordinate2D)coordinate;

/**
 * @brief 长按地图，返回经纬度。注意：使用长按手势，需要实现longPressGesture:方法，具体参考demo实现LongGestureViewController
 * @param map 地图View
 * @param coordinate 经纬度
 */
- (void)map:(MAMap *)map didLongPressedAtCoordinate:(CLLocationCoordinate2D)coordinate;

@end

NS_ASSUME_NONNULL_END
