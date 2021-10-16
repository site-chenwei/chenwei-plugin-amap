//
//  MAPathShowRange.h
//  MAMapKit
//
//  Created by shaobin on 2019/12/31.
//  Copyright © 2019 Amap. All rights reserved.
//

#ifndef MAPathShowRange_h
#define MAPathShowRange_h

struct MAPathShowRange {
    float begin;         ///<起点位置，整数部分表示起点索引，小数部分表示在线段上的位置
    float end;           ///<终点位置，整数部分表示起点索引，小数部分表示在线段上的位置
};

typedef struct MAPathShowRange MAPathShowRange;

static inline MAPathShowRange MAPathShowRangeMake(float begin, float end) {
    return (MAPathShowRange){begin, end};
}


#endif /* MAPathShowRange_h */
