//
//  MATopographyOverlay.h
//  MAMapKit
//
//  Created by JZ on 2021/3/17.
//  Copyright © 2021 Amap. All rights reserved.
//

#import "MAMapKit.h"

NS_ASSUME_NONNULL_BEGIN

@interface MATerrainOverlay : MATileOverlay

///terrainURLTemplate获取地形数据，默认使用高德地形数据
@property (readonly) NSString *terrainURLTemplate;

///terrainTextureURLTemplate获取地形纹理数据，默认使用高德卫星数据
@property (readonly) NSString *terrainTextureURLTemplate;

/**
 * @brief 初始化地形overlay
 */
- (instancetype)initDefaultTerrainOverlay;

@end

NS_ASSUME_NONNULL_END
