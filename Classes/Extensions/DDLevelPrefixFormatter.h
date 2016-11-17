//
//  DDLevelPrefixFormatter.h
//  Lumberjack
//
//  Created by lee on 16/11/17.
//
//

#import <Foundation/Foundation.h>

// Disable legacy macros
#ifndef DD_LEGACY_MACROS
#define DD_LEGACY_MACROS 0
#endif


#import "DDLog.h"

@interface DDLevelPrefixFormatter : NSObject <DDLogFormatter>

@property (nonatomic, strong) NSDateFormatter *DateFormatter;
@end
