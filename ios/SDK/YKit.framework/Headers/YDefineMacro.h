//
//  YDefineMacro.h
//  YKit
//
//  Created by Loc Nguyen on 7/31/16.
//  Copyright © 2016 YGame. All rights reserved.
//

#ifndef YDefineMacro_h
#define YDefineMacro_h

#define def_event(__name__) \
static NSString* Event_##__name__ = @"evt_"#__name__

#define def_event_request(__name__) \
static NSString* Request_##__name__ = @"req_"#__name__

#define def_event_response(__name__) \
static NSString* Response_##__name__ = @"res_"#__name__

#define def_event_combo(__name__) \
static NSString* Request_##__name__ = @"req_"#__name__; \
static NSString* Response_##__name__##_Success = @"res_"#__name__"_success"; \
static NSString* Response_##__name__##_Fail = @"res_"#__name__"_fail"


#define ATDispatchEvent(__event__, __data__) [[NSNotificationCenter defaultCenter] postNotificationName:__event__ object:nil userInfo:__data__]

#define ATAddObserver(__selector__, __event__) [[NSNotificationCenter defaultCenter] addObserver:self selector:__selector__ name:__event__ object:nil]

#define ATNonNilObject(__object__) __object__ != nil ? __object__ : [NSNull null]
#define ATCastNilObject(__object__) [__object__ isKindOfClass:[NSNull class]] ? nil : __object__

#define UniValue(__value1__, __value2__) (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone ? __value1__ : __value2__)

#endif /* YDefineMacro_h */
