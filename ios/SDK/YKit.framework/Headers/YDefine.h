//
//  YDefine.h
//  YKit
//
//  Created by Loc Nguyen on 7/31/16.
//  Copyright © 2016 YGame. All rights reserved.
//

#ifndef YDefine_h
#define YDefine_h

#include "YDefineMacro.h"

// other param
#define kParamTitle                 @"title"
#define kParamMessage               @"msg"
#define kParamSocialID              @"id"
#define kParamSocialName            @"name"
#define kParamSocialEmail           @"email"
#define kParamSocialAvatarUrl       @"url"
#define kParamSocialPicture         @"picture"
#define kParamSocialPictureData     @"data"
#define kParamUrl                   @"url"
#define kParamOptions               @"options"
#define kParamApplication           @"application"
#define kParamSourceApplication     @"sourceApplication"
#define kParamAnnotation            @"annotation"
#define kParamProductID             @"productId"
#define kParamActiveEmail           @"activeEmail"
#define kParamActivePhone           @"activePhone"
#define kParamUserName              @"username"
#define kParamID                    @"id"
#define kParamIconUrl               @"iconUrl"
#define kParamUserID                @"userID"
#define kParamStatus                @"status"
#define kParamIs0                   @"is0"
#define kParamIs1                   @"is1"
#define kParamIs2                   @"is2"
#define kParamIs3                   @"is3"
#define kParamData                  @"data"
#define kParamDataTemplate          @"data%d"
#define kParamAmountString          @"amountString"
#define kParamValue                 @"value"
#define kParamTypePay               @"typePay"
#define kParamReceipt               @"receiptData"
#define kParamPaymentExtraData      @"gameOrder"
#define kParamCallbackURL           @"callbackUrl"
#define kParamAccessToken           @"accessToken"
#define kParamUser                  @"user"
#define kParamMail                  @"mail"
#define kParamAccessTokenFB         @"access_token"
#define kParamFacebookId            @"fb_id"
// system event
def_event(AppDidFinishLaunching);
def_event(AppDidBecomeActive);
def_event(AppOpenUrl);
def_event(AppOpenUrlEx);


typedef NS_ENUM(NSInteger, ATButtonStickySide)
{
    None                        = 0,
    ATButtonStickySideTop       = 1 << 0,
    ATButtonStickySideBottom    = 1 << 1,
    ATButtonStickySideLeft      = 1 << 2,
    ATButtonStickySideRight     = 1 << 3,
    ATButtonStickySideAll       = ATButtonStickySideTop | ATButtonStickySideBottom | ATButtonStickySideLeft | ATButtonStickySideRight
};



@protocol PaymentExtraDataProtocol <NSObject>
- (NSString *)getPaymentExtraData;
@end

#endif /* YDefine_h */
