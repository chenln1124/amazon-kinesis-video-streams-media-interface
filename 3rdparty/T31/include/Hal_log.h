#ifndef HAL_LOG_H
#define HAL_LOG_H

#ifdef HAL_USE_AONI_SYSLOG
#include "../../Common/include/syslog.h"
#else
#include <time.h>
#include <string.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef void (*LOG_FUNC)(int level, const char* fmt, va_list args);

/*****************************************************************************
 Prototype    : Hal_SYSLOG_Set_LogPrintLevel
 Description  : 设置打印等级，只有当前打印等级<=设定的Log                PrintLevel时，才会打印
 Input        : int LogPrintLevel  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/28
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_SYSLOG_Set_LogPrintLevel(int LogPrintLevel);
extern void Hal_SYSLOG_Set_External_Log(LOG_FUNC pLogFunc);


extern void Hal_SYSLOG(int priority, char *fmt,...);

#define    LOG_TRACE	4
#define    LOG_DEBUG	3
#define    LOG_INFO		2
#define    LOG_WARN		1
#define    LOG_ERR		0
#define COMM_SYSLOG(log_level, fmt, args...)	Hal_SYSLOG(log_level, "[%s:%d] " fmt, __FUNCTION__, __LINE__, ##args)

#endif

#endif /* HAL_LOG_H */
