//
//  DDLogMacrosCus.h
//  Lumberjack
//
//  Created by lee on 16/11/17.
//
//

#ifndef DDLogMacrosCus_h
#define DDLogMacrosCus_h

// Disable legacy macros
#ifndef DD_LEGACY_MACROS
#define DD_LEGACY_MACROS 0
#endif

#import "DDLog.h"

/**
 * The constant/variable/method responsible for controlling the current log level.
 **/
#ifndef LOG_LEVEL_DEF
#define LOG_LEVEL_DEF ddLogLevel
#endif

/**
 * Whether async should be used by log messages, excluding error messages that are always sent sync.
 **/
#ifndef LOG_ASYNC_ENABLED
#define LOG_ASYNC_ENABLED YES
#endif

/**
 * These are the two macros that all other macros below compile into.
 * These big multiline macros makes all the other macros easier to read.
 **/
#define LOG_MACRO(isAsynchronous, lvl, flg, ctx, atag, fnct, frmt, ...) \
[DDLog log : isAsynchronous                                     \
level : lvl                                                \
flag : flg                                                \
context : ctx                                                \
file : __FILE__                                           \
function : fnct                                               \
line : __LINE__                                           \
tag : atag                                               \
format : (frmt), ## __VA_ARGS__]

#define LOG_MACRO_TO_DDLOG(ddlog, isAsynchronous, lvl, flg, ctx, atag, fnct, frmt, ...) \
[ddlog log : isAsynchronous                                     \
level : lvl                                                \
flag : flg                                                \
context : ctx                                                \
file : __FILE__                                           \
function : fnct                                               \
line : __LINE__                                           \
tag : atag                                               \
format : (frmt), ## __VA_ARGS__]

/**
 * Define version of the macro that only execute if the log level is above the threshold.
 * The compiled versions essentially look like this:
 *
 * if (logFlagForThisLogMsg & ddLogLevel) { execute log message }
 *
 * When LOG_LEVEL_DEF is defined as ddLogLevel.
 *
 * As shown further below, Lumberjack actually uses a bitmask as opposed to primitive log levels.
 * This allows for a great amount of flexibility and some pretty advanced fine grained logging techniques.
 *
 * Note that when compiler optimizations are enabled (as they are for your release builds),
 * the log messages above your logging threshold will automatically be compiled out.
 *
 * (If the compiler sees LOG_LEVEL_DEF/ddLogLevel declared as a constant, the compiler simply checks to see
 *  if the 'if' statement would execute, and if not it strips it from the binary.)
 *
 * We also define shorthand versions for asynchronous and synchronous logging.
 **/
#define LOG_MAYBE(async, lvl, flg, ctx, tag, fnct, frmt, ...) \
do { if(lvl & flg) LOG_MACRO(async, lvl, flg, ctx, tag, fnct, frmt, ##__VA_ARGS__); } while(0)

#define LOG_MAYBE_TO_DDLOG(ddlog, async, lvl, flg, ctx, tag, fnct, frmt, ...) \
do { if(lvl & flg) LOG_MACRO_TO_DDLOG(ddlog, async, lvl, flg, ctx, tag, fnct, frmt, ##__VA_ARGS__); } while(0)

/**
 * Ready to use log macros with no context or tag.
 **/
#define DDLogError(frmt, ...)   LOG_MAYBE(NO,                LOG_LEVEL_DEF, DDLogFlagError,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define DDLogWarn(frmt, ...)    LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, DDLogFlagWarning, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define DDLogInfo(frmt, ...)    LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, DDLogFlagInfo,    0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define DDLogDebug(frmt, ...)   LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, DDLogFlagDebug,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define DDLogVerbose(frmt, ...) LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, DDLogFlagVerbose, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)

#define DDLogErrorToDDLog(ddlog, frmt, ...)   LOG_MAYBE_TO_DDLOG(ddlog, NO,                LOG_LEVEL_DEF, DDLogFlagError,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define DDLogWarnToDDLog(ddlog, frmt, ...)    LOG_MAYBE_TO_DDLOG(ddlog, LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, DDLogFlagWarning, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define DDLogInfoToDDLog(ddlog, frmt, ...)    LOG_MAYBE_TO_DDLOG(ddlog, LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, DDLogFlagInfo,    0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define DDLogDebugToDDLog(ddlog, frmt, ...)   LOG_MAYBE_TO_DDLOG(ddlog, LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, DDLogFlagDebug,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define DDLogVerboseToDDLog(ddlog, frmt, ...) LOG_MAYBE_TO_DDLOG(ddlog, LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, DDLogFlagVerbose, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)


// level context tag
#define LOGE DDLogError
#define LOGW DDLogWarn
#define LOGI DDLogInfo
#define LOGD DDLogDebug
#define LOGV DDLogVerbose











#endif /* DDLogMacrosCus_h */
