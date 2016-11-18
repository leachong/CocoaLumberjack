//
//  DDLevelPrefixFormatter.m
//  Lumberjack
//
//  Created by lee on 16/11/17.
//
//

#import "DDLevelPrefixFormatter.h"

@implementation DDLevelPrefixFormatter

- (instancetype)init {
    self = [super init];
    if (self != nil) {
        _DateFormatter = [[NSDateFormatter alloc] init];
        [_DateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss:SSS"];
    }
    return self;
}

- (NSString *)formatLogMessage:(DDLogMessage *)logMessage {
    NSString *logLevel;
    switch (logMessage->_flag) {
        case DDLogFlagError    : logLevel = @"E"; break;
        case DDLogFlagWarning  : logLevel = @"W"; break;
        case DDLogFlagInfo     : logLevel = @"I"; break;
        case DDLogFlagDebug    : logLevel = @"D"; break;
        case DDLogFlagVerbose  : logLevel = @"V"; break;
        default                : logLevel = @"U"; break;
    }
    NSString *dateString = logMessage->_timestamp == nil ? @"" : [_DateFormatter stringFromDate:logMessage->_timestamp];
    
    
    NSString* queueStr = @"";
    if (_HasQueueLabel) {
        queueStr = [NSString stringWithFormat:@" | %@", logMessage->_queueLabel];
    }
    NSString* fileNameStr = @"";
    if (_HasFileName) {
        fileNameStr = [NSString stringWithFormat:@" | %@", logMessage->_fileName];
    }
    NSString* messageStr = @"";
    if (_HasQueueLabel || _HasFileName) {
        messageStr = [NSString stringWithFormat:@" | %@", logMessage->_message];
    } else {
        messageStr = [NSString stringWithFormat:@" %@", logMessage->_message];
    }
    
    NSString* tmp = [NSString stringWithFormat:@"%@ [%@]%@%@%@", dateString, logLevel, queueStr, fileNameStr, messageStr];
    
//    NSLog(tmp);
    
    return tmp;
}
@end
