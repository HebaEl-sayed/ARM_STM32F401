#include "C:/Users/LEGION/Desktop/C/LOG/LOG.h"

static FILE *logFile = NULL;
static LOG_level_t logSeverity = INFO;
static LOG_OUTPUTCHANNEL_t outputChannel = consolechannel;

void Setlogoutput_channel(LOG_OUTPUTCHANNEL_t output_ch) {
    outputChannel = output_ch;
}

void Setlog_severity(LOG_level_t log_priority) {
    logSeverity = log_priority;
}

void Write_log(LOG_level_t Type, const char* format, ...) {
    va_list args;
    va_start(args, format);

    time_t NOW;
    struct tm *timeinfo;
    time(&NOW);
    timeinfo = localtime(&NOW);
    char timestamp[20];
    strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", timeinfo);


    
    if (Type >= logSeverity) {
     
        if (outputChannel == consolechannel) {
            printf("[%s] ", timestamp);
            switch (Type) {
                case INFO:
                    printf("INFO: ");
                    break;
                case WARNING:
                    printf("WARNING: ");
                    break;
                case ERROR:
                    printf("ERROR: ");
                    break;
                case CRITICAL:
                    printf("CRITICAL: ");
                    break;
                default:
                    break;
            }
            vprintf(format, args);
            printf("\n");
        }

      
        if (outputChannel == filechannel && logFile != NULL) {
            fprintf(logFile, "[%s] ", timestamp);
            switch (Type) {
                case INFO:
                    fprintf(logFile, "INFO: ");
                    break;
                case WARNING:
                    fprintf(logFile, "WARNING: ");
                    break;
                case ERROR:
                    fprintf(logFile, "ERROR: ");
                    break;
                case CRITICAL:
                    fprintf(logFile, "CRITICAL: ");
                    break;
                default:
                    break;
            }
            vfprintf(logFile, format, args);
            fprintf(logFile, "\n");
            fflush(logFile); 
        }
    }

    va_end(args);
}



void LogFile_cfg(const char* new_file) {

    logFile = fopen(new_file, "a"); 
    if (logFile == NULL) {
        printf("Error: Unable to open the log file.\n");
    }
        if (logFile != NULL) {
        fclose(logFile); 
    }
}
