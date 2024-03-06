#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

typedef enum
{
 INFO ,
 WARNING ,
 ERROR ,
 CRITICAL
}LOG_level_t ;

typedef enum
{
  consolechannel,
  filechannel

}LOG_OUTPUTCHANNEL_t ;

void Setlogoutput_channel (LOG_OUTPUTCHANNEL_t output_ch);
void Write_log(LOG_level_t Type, const char* format, ... );
void Setlog_severity(LOG_level_t log_priority);
void LogFile_cfg(const char* new_file);

#endif