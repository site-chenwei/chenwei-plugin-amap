//
//  MACustomSchemeModel.h
//  MAMapKit
//
//  Created by JZ on 2021/1/21.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MACustomSchemeModel : NSObject

//自定义schemeName
@property(nonatomic, readonly, strong) NSString *urlScheme;

//自定义schemeHandler。 注意：只在iOS11及以后有值
@property(nonatomic, readonly, strong) NSObject<WKURLSchemeHandler> *urlSchemeHandler API_AVAILABLE(ios(11.0));

@end

NS_ASSUME_NONNULL_END
