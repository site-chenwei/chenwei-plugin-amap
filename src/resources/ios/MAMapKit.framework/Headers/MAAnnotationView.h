//
//  MAAnnotationView.h
//  MAMapKitDemo
//
//  Created by songjian on 13-1-7.
//  Copyright © 2016 Amap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MACustomCalloutView.h"

///MAAnnotationView拖动状态
typedef NS_ENUM(NSInteger, MAAnnotationViewDragState)
{
    MAAnnotationViewDragStateNone = 0,      ///< 静止状态
    MAAnnotationViewDragStateStarting,      ///< 开始拖动
    MAAnnotationViewDragStateDragging,      ///< 拖动中
    MAAnnotationViewDragStateEnding         ///< 拖动结束
};

@protocol MAAnnotation;

///标注view
@interface MAAnnotationView : NSObject

///z值，大值在上，默认为0。类似CALayer的zPosition。 默认为100
@property (nonatomic, assign) NSInteger zIndex;

///关联的annotation
@property (nonatomic, strong) id <MAAnnotation> annotation;

///显示的image
@property (nonatomic, strong) UIImage *image;

///自定制弹出框view, 用于替换默认弹出框. 注意:此弹出框不会触发-(void)map: didAnnotationViewCalloutTapped:
@property (nonatomic, strong) MACustomCalloutView *customCalloutView;

///annotationView的中心默认位于annotation的坐标位置，可以设置centerOffset改变view的位置，正的偏移使view朝右下方移动，负的朝左上方，单位是屏幕坐标
@property (nonatomic) CGPoint centerOffset;

///弹出框默认位于view正中上方，可以设置calloutOffset改变view的位置，正的偏移使view朝右下方移动，负的朝左上方，单位是屏幕坐标
@property (nonatomic) CGPoint calloutOffset;

///默认为YES,当为NO时view忽略触摸事件
@property (nonatomic, getter=isEnabled) BOOL enabled;

///是否可见，默认为YES
@property (nonatomic, assign) BOOL isVisible;

///设置是否处于选中状态, 外部如果要选中请使用map的selectAnnotation方法
@property (nonatomic, getter=isSelected) BOOL selected;

///是否允许弹出callout
@property (nonatomic) BOOL canShowCallout;

///显示在默认弹出框左侧的view
@property (nonatomic, strong) UIView *leftCalloutAccessoryView;

///显示在默认弹出框右侧的view
@property (nonatomic, strong) UIView *rightCalloutAccessoryView;

///是否支持点击，默认YES
@property (nonatomic, getter=isClickable) BOOL clickable;

///是否支持拖动，默认NO
@property (nonatomic, getter=isDraggable) BOOL draggable;

///当前view的拖动状态
@property (nonatomic) MAAnnotationViewDragState dragState;

/**
 * @brief 初始化并返回一个annotation view
 * @param annotation      关联的annotation对象
 * @return 初始化成功则返回annotation view,否则返回nil
 */
- (id)initWithAnnotation:(id <MAAnnotation>)annotation;

/**
 * @brief 当关联annotation/annotationView对象有更新时，调用此接口刷新.
 */
- (void)setNeedsUpdate;

@end
