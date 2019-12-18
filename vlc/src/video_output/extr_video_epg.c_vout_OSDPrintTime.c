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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 

__attribute__((used)) static char * vout_OSDPrintTime(time_t t)
{
    char *psz;
    struct tm tms;
    localtime_r(&t, &tms);
    if(asprintf(&psz, "%2.2d:%2.2d", tms.tm_hour, tms.tm_min) < 0)
       psz = NULL;
    return psz;
}