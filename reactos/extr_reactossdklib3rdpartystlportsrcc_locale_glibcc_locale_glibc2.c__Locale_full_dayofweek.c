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
struct _Locale_time {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 scalar_t__ DAY_1 ; 
 char const* nl_langinfo_l (scalar_t__,int /*<<< orphan*/ ) ; 

const char *_Locale_full_dayofweek(struct _Locale_time *__loc, int _d )
{
  return nl_langinfo_l(DAY_1 + _d, (locale_t)__loc);
}