#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int LOG_LEVEL ;

/* Variables and functions */
 int LOG_ERR ; 
 int LOG_INFO ; 
#define  LOG_LEVEL_ERROR 130 
#define  LOG_LEVEL_INFO 129 
#define  LOG_LEVEL_WARNING 128 
 int LOG_WARNING ; 

int level_syslog(LOG_LEVEL level)
{
    switch (level) {
        case LOG_LEVEL_INFO:
            return LOG_INFO;

        case LOG_LEVEL_WARNING:
            return LOG_WARNING;

        case LOG_LEVEL_ERROR:
            return LOG_ERR;
    }

    return LOG_INFO;
}