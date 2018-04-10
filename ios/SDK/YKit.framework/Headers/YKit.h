//
//  YKit.h
//  YKit
//
//  Created by Loc Nguyen Tan on 8/2/16.
//  Copyright © 2016 YGame. All rights reserved.
//
//#import <AppsFlyer/AppsFlyer.h>
//#import "AppsFlyerUtility.h"
#import <UIKit/UIKit.h>
#import "AppsFlyer.h"

//! Project version number for YKit.
FOUNDATION_EXPORT double YKitVersionNumber;

//! Project version string for YKit.
FOUNDATION_EXPORT const unsigned char YKitVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <YKit/PublicHeader.h>

#import "YDefine.h"

@interface YKit : NSObject <AppsFlyerTrackerDelegate, UIAlertViewDelegate>
@property (nonatomic, assign) BOOL isPotrait;
@property (nonatomic, readonly) BOOL isSetup;
@property (nonatomic, strong) UIWindow *atWindow;
// singleton
+ (id)getInstance;

// setup
- (void)setupWithWindow:(UIWindow *)window usingFacebookSDK:(BOOL)usingFaceookSDK;
- (void)setServerTest:(BOOL)isTest;
- (AppsFlyerTracker*)getAppflyer;
// for push notification
- (void) appDidReceiveMessage:(NSDictionary *)userInfo;
// for launcher
- (void)setPermissionFacebook:(NSString *)permission;
- (NSDictionary *)checkFacebookAccessToken;
- (NSDictionary *)getFacebookInfo;
- (void)setLauncherStickySide:(ATButtonStickySide)side;
- (void)showButtonLauncherWithAnimation:(BOOL)anim;
- (void)hideButtonLauncherWithAnimation:(BOOL)anim;
- (void)showLoginScreen;
- (void)showAssisstantScreen;
- (void)showHistoryTrade;
- (void)showPaymentScreen;
- (void)showUserInfoScreen;
- (BOOL)silentLogin;
- (int)getCoin;
//- (void)setGameOrder:(NSString *)gameOrder;
- (BOOL)setPaymentInfo:(NSString*)serverId andCharId:(NSString*)charId andPayment:(NSString*)payment;
- (void)buyItemWithGameOrder;
- (void)setBlurAlpha:(NSInteger)alpha;
- (void)shareFacebookWithImage:(UIImage *)image;
// for callback
- (void)setPaymentExtraDataObject:(NSObject<PaymentExtraDataProtocol> *)object;
- (void)handleLoginWithCompletion:(void (^) (NSDictionary *data))completion;
- (void)handleLogoutWithCompletion:(void (^) ())completion;
- (void)handlePaymentWithCompletion:(void (^) (NSDictionary *data))completion;
- (void)handleShowSDKCompletion:(void (^)())completion;
- (void)handleCloseSDKCompletion:(void (^)())completion;
// for orientation
-(void)potraitOnly:(BOOL)value;
-(BOOL)isScreenRotateToPortrait;
// for internal usage
- (NSString *)getPaymentExtraData;
- (NSDictionary*)getGameModel;
// setKey
- (void)reloadMenu;
- (void)setAppsFlyerDevKey:(NSString *)devKey appID:(NSString *)appID;
- (void)setACTConversionID:(NSString *)conversionID andLabel:(NSString *)label andValue:(NSString *)value;
- (void)setGoogleAnalyticsID:(NSString *)analyticsID;
- (void) setFCMToken:(NSString*) fcm_Token;
- (void)setPaymentID:(NSString *)paymentID;

- (BOOL)buy:(NSString*)serverId char_id:(NSString*)charId payment_id:(NSString*)payment isConfirm:(bool)is_confirm;
@end
