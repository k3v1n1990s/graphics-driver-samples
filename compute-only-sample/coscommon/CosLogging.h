#ifndef _COSLOGGING_H_
#define _COSLOGGING_H_ 1

//
// Copyright (C) Microsoft. All rights reserved.
//
// WPP tracing configuration file shared between usermode and kernel mode.
//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//
// Debug/Bugcheck helpers used by tracing macros.
// NOTE: These are not intended to be called from anywhere else
//
extern int _CosLogBugcheck (ULONG Level);
extern int _CosLogDebug (ULONG Level);
    
// begin_wpp config
//
// FUNC COS_LOG_CRITICAL_ERROR{LEVEL=TRACE_LEVEL_CRITICAL, FLAGS=COS_TRACING_BUGCHECK}(MSG, ...);
// USEPREFIX (COS_LOG_CRITICAL_ERROR, "%!STDPREFIX! [%s @ %u] CRITICAL ERROR:", __FILE__, __LINE__);
//
// FUNC COS_LOG_ASSERTION{LEVEL=TRACE_LEVEL_ERROR, FLAGS=COS_TRACING_DEBUG}(MSG, ...);
// USEPREFIX (COS_LOG_ASSERTION, "%!STDPREFIX! [%s @ %u] ASSERTION :", __FILE__, __LINE__);
//
// FUNC COS_LOG_ERROR{LEVEL=TRACE_LEVEL_ERROR, FLAGS=COS_TRACING_DEFAULT}(MSG, ...);
// USEPREFIX (COS_LOG_ERROR, "%!STDPREFIX! [%s @ %u] ERROR :", __FILE__, __LINE__);
//
// FUNC COS_LOG_LOW_MEMORY{LEVEL=TRACE_LEVEL_ERROR, FLAGS=COS_TRACING_DEFAULT}(MSG, ...);
// USEPREFIX (COS_LOG_LOW_MEMORY, "%!STDPREFIX! [%s @ %u] LOW MEMORY :", __FILE__, __LINE__);
//
// FUNC COS_LOG_WARNING{LEVEL=TRACE_LEVEL_WARNING, FLAGS=COS_TRACING_DEFAULT}(MSG, ...);
// USEPREFIX (COS_LOG_WARNING, "%!STDPREFIX! [%s @ %u] WARNING :", __FILE__, __LINE__);
//
// FUNC COS_LOG_INFORMATION{LEVEL=TRACE_LEVEL_INFORMATION, FLAGS=COS_TRACING_DEFAULT}(MSG, ...);
// USEPREFIX (COS_LOG_INFORMATION, "%!STDPREFIX! [%s @ %u] INFO :", __FILE__, __LINE__);
//
// FUNC COS_LOG_TRACE{LEVEL=TRACE_LEVEL_VERBOSE, FLAGS=COS_TRACING_DEFAULT}(MSG, ...);
// USEPREFIX (COS_LOG_TRACE, "%!STDPREFIX! [%s @ %u] TRACE :", __FILE__, __LINE__);
//
// FUNC COS_TRACE_EVENTS(LEVEL, FLAGS, MSG, ...);
// USEPREFIX (COS_TRACE_EVENTS, "%!STDPREFIX! [%s @ %u] TRACE :", __FILE__, __LINE__);
//
// FUNC COS_CRITICAL_ASSERT{LEVEL=TRACE_LEVEL_CRITICAL, FLAGS=COS_TRACING_BUGCHECK}(COS_CRIT_ASSERT_EXP);
// USEPREFIX (COS_CRITICAL_ASSERT, "%!STDPREFIX! [%s @ %u] CRITICAL ASSERTION :%s", __FILE__, __LINE__, #COS_CRIT_ASSERT_EXP);
//
// FUNC COS_ASSERT{LEVEL=TRACE_LEVEL_ERROR, FLAGS=COS_TRACING_DEBUG}(COS_ASSERT_EXP);
// USEPREFIX (COS_ASSERT, "%!STDPREFIX! [%s @ %u] ASSERTION :%s", __FILE__, __LINE__, #COS_ASSERT_EXP);
//
// end_wpp


//
// COS_LOG... customization
//

#define WPP_LEVEL_FLAGS_POST(LEVEL,FLAGS) \
    ,(((WPP_BIT_ ## FLAGS) == WPP_BIT_COS_TRACING_BUGCHECK) ? \
            _CosLogBugcheck(LEVEL) : \
            (((WPP_BIT_ ## FLAGS) == WPP_BIT_COS_TRACING_DEBUG) ? \
                _CosLogDebug(LEVEL) : 1))

//
// COS_CRTITICAL_ASSERT customization
//

#define WPP_RECORDER_LEVEL_FLAGS_COS_CRIT_ASSERT_EXP_FILTER(LEVEL, FLAGS, COS_CRIT_ASSERT_EXP) \
    (!(COS_CRIT_ASSERT_EXP))

#define WPP_RECORDER_LEVEL_FLAGS_COS_CRIT_ASSERT_EXP_ARGS(LEVEL, FLAGS, COS_CRIT_ASSERT_EXP) \
    WPP_CONTROL(WPP_BIT_ ## FLAGS).AutoLogContext, LEVEL, WPP_BIT_ ## FLAGS

#define WPP_LEVEL_FLAGS_COS_CRIT_ASSERT_EXP_POST(LEVEL, FLAGS, COS_CRIT_ASSERT_EXP) \
    ,((!(COS_CRIT_ASSERT_EXP)) ? _CosLogBugcheck(LEVEL) : 1)

//
// COS_ASSERT customization
//

#define WPP_RECORDER_LEVEL_FLAGS_COS_ASSERT_EXP_FILTER(LEVEL, FLAGS, COS_ASSERT_EXP) \
    (!(COS_ASSERT_EXP))

#define WPP_RECORDER_LEVEL_FLAGS_COS_ASSERT_EXP_ARGS(LEVEL, FLAGS, COS_ASSERT_EXP) \
    WPP_CONTROL(WPP_BIT_ ## FLAGS).AutoLogContext, LEVEL, WPP_BIT_ ## FLAGS

#define WPP_LEVEL_FLAGS_COS_ASSERT_EXP_POST(LEVEL, FLAGS, COS_ASSERT_EXP) \
    ,((!(COS_ASSERT_EXP)) ? _CosLogDebug(LEVEL) : 1)


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // _COSLOGGING_H_

