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
typedef  struct tm const tm ;
typedef  struct tm time_t ;

/* Variables and functions */
 struct tm const* errno ; 
 struct tm const* gmtime_r (struct tm const*,struct tm const*) ; 
 struct tm const* localtime_s (struct tm const*,struct tm const*) ; 

struct tm *localtime_r (const time_t *timep, struct tm *result)
{
#if (__STDC_WANT_LIB_EXT1__)
    return localtime_s(timep, result);
#elif defined (_WIN32)
    return ((errno = localtime_s(result, timep)) == 0) ? result : NULL;
#else
# warning localtime_r() not implemented!
    return gmtime_r(timep, result);
#endif
}