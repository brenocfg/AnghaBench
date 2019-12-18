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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  LOG_LEVEL_ERROR 130 
#define  LOG_LEVEL_INFO 129 
#define  LOG_LEVEL_WARNING 128 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

FILE *level_stdout(LOG_LEVEL level)
{
    switch (level) {
        case LOG_LEVEL_INFO:
            return stdout;

        case LOG_LEVEL_WARNING: // intentional fallthrough
        case LOG_LEVEL_ERROR:
            return stderr;
    }

    return stdout;
}