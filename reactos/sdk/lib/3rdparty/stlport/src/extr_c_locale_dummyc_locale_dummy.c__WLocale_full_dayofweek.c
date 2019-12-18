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
typedef  int /*<<< orphan*/  wchar_t ;
struct _Locale_time {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  const** full_wdayname ; 

const wchar_t * _WLocale_full_dayofweek(struct _Locale_time * ltime, int n,
                                        wchar_t* buf, size_t bufSize)
{ return full_wdayname[n]; }