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
struct tm {int dummy; } ;
typedef  int __time64_t ;
typedef  int /*<<< orphan*/  __time32_t ;

/* Variables and functions */
 int MAX_32BIT_TIME ; 
 int mktime_worker (struct tm*,int /*<<< orphan*/ ) ; 

__time32_t
_mktime32(struct tm *ptm)
{
    __time64_t time = mktime_worker(ptm, 0);
    return (__time32_t)((time > MAX_32BIT_TIME) ? -1 : time);
}