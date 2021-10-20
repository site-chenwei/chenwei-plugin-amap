//
//  MAMapWebViewProcotol.h
//  MAMapKit
//
//  Created by JZ on 2021/1/7.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MAMapWebViewProcotol <NSObject>

/**
 * @brief 获取WKWebView的configuration
 */
- (WKWebViewConfiguration*)configuration;

/**
 * @brief 加载HTML
 * @param baseURL 加载的baseURL
 */
- (nullable WKNavigation *)loadHTMLString:(NSString *)string baseURL:(nullable NSURL *)baseURL;

/**
 * @brief 加载request
 * @param request request
 */
- (nullable WKNavigation *)loadRequest:(NSURLRequest *)request;

/**
 * @brief 执行JS脚本
 * @param completionHandler 执行结果回调
 */
- (void)evaluateJavaScript:(NSString *)javaScriptString completionHandler:(void (^ _Nullable)(_Nullable id, NSError * _Nullable error))completionHandler;

@optional

/**
 * @brief 向视图上添加子view
 * @param view 需要添加的view
 */
- (void)addSubView:(UIView*)view;

@end

NS_ASSUME_NONNULL_END
