//
//  WrapperIOS.m
//  XLauncher
//
//  Created by Trung Le Bao on 12/30/16.
//  Copyright © 2016 XCT. All rights reserved.
//

#import "WrapperIOS.h"
#import <XLauncher/XLauncher.h>
@implementation WrapperIOS
void showPaymentScreenFromUnity() {
    [[XLauncher getInstance] showPaymentScreen];
}
void setGameOrder(char *gameOrder) {
    [[XLauncher getInstance] setGameOrder:[NSString stringWithUTF8String:gameOrder]];
}
void showLoginScreen() {
    [[XLauncher getInstance] showLoginScreen];
}
void silentLogin() {
    [[XLauncher getInstance] silentLogin];
}
@end

