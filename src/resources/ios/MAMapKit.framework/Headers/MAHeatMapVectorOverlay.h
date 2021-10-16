//
//  MAHeatMapVectorOverlay.h
//  MAMapKit
//
//  Created by ldj on 2019/7/25.
//  Copyright © 2019 Amap. All rights reserved.
//

#import "MAConfig.h"
#if MA_INCLUDE_OVERLAY_HEATMAP

#import "MAShape.h"
#import "MAOverlay.h"

///热力图类型
typedef NS_ENUM(NSInteger, MAHeatMapType)
{
    MAHeatMapTypeSquare      = 1,     ///< 网格热力图
    MAHeatMapTypeHoneycomb   = 2      ///< 蜂窝热力图
};

///单个点对象
@interface MAHeatMapVectorNode : NSObject

///经纬度
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

///权重
@property (nonatomic, assign) float weight;

@end

///热力图展示节点（用以描述一个蜂窝或一个网格）
@interface MAHeatMapVectorItem : NSObject

///中心点坐标
@property (nonatomic, readonly) MAMapPoint center;

///当前热力值，求和后的权重
@property (nonatomic, readonly) float intensity;

///落在此节点区域内的所有热力点的索引数组
@property (nonatomic, readonly) NSArray<NSNumber *> *nodeIndices;

@end

///该类用于定义热力图属性.
@interface MAHeatMapVectorOverlayOptions : NSObject

///热力图类型 (默认为蜂窝类型MAHeatMapTypeHoneycomb)
@property (nonatomic, assign) MAHeatMapType type;

///option选项是否可见. (默认YES)
@property (nonatomic, assign) BOOL visible;

///MAHeatMapVectorNode array
@property (nonatomic, strong) NSArray<MAHeatMapVectorNode *> *inputNodes;

/**
 @verbatim
 节点的宽 单位：米 负数按照0处理 default 2000
     —— ——    —— ——
   丨     丨 丨     丨
   丨     丨 丨     丨
     —— ——    —— ——
 
 每个方框的宽就是 size（六边形同理）
 两个方框之间的间隔就是 gap （六边形同理）
 @endverbatim
 */
@property (nonatomic, assign) CLLocationDistance size;

///节点之间的间隔 单位：米 负数按照0处理。注意：改变gap可能会改变热力节点的计算，内部会用size+gap来计算热力，最终用size来画方框。
@property (nonatomic, assign) CGFloat gap;

///颜色变化数组。 注意：colors和startPoints两数组长度必须一致且不能为0，
@property (nonatomic, strong) NSArray<UIColor *> *colors;

///颜色变化起点，需为递增数组，区间为[0, 1]。 注意：colors和startPoints两数组长度必须一致且不能为0。例如：startPoints @[@(0), @(0.3),@(0.7)] 表示区间 [0,0.3)使用第一个颜色，区间[0.3,0.7)使用第二个颜色，区间[0.7,1]使用第三个颜色。注意：startPoints首位需设置成0，如果首位不是0，内部也会把首位当成0来处理。
@property (nonatomic, strong) NSArray<NSNumber *> *startPoints;

///透明度，取值范围[0,1] ，default为1不透明
@property (nonatomic, assign) CGFloat opacity __attribute((deprecated("已废弃，since 7.9.0，请使用MAHeatMapVectorOverlayRender中的alpha")));;

///权重的最大值，default为0，表示不填，不填则取数组inputNodes中权重的最大值
@property (nonatomic, assign) int maxIntensity;

///最小显示级别 default 3
@property (nonatomic, assign) CGFloat minZoom;

///最大显示级别 default 20
@property (nonatomic, assign) CGFloat maxZoom;

@end

///矢量热力图，支持类型详见MAHeatMapType
@interface MAHeatMapVectorOverlay : MAShape<MAOverlay>

///热力图的配置属性
@property (nonatomic, strong) MAHeatMapVectorOverlayOptions *option;

/**
 * @brief 根据配置属性option生成MAHeatMapVectorOverlay
 * @param option 热力图配置属性option
 * @return 新生成的热力图MAHeatMapVectorOverlay
 */
+ (instancetype)heatMapOverlayWithOption:(MAHeatMapVectorOverlayOptions *)option;

@end

#endif
