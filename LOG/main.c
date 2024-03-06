#include "C:/Users/LEGION/Desktop/C/LOG/LOG.h"
int main(void)
{
    Setlogoutput_channel(consolechannel);
   // LogFile_cfg("logtest");
    Setlog_severity(CRITICAL);
    Write_log(CRITICAL,"this is a critical message %d",0);
    return 0;
}