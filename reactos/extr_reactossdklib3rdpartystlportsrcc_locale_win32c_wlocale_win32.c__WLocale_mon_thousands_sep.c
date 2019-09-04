#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/ * thousands_sep; } ;
typedef  TYPE_1__ _Locale_monetary_t ;

/* Variables and functions */

wchar_t _WLocale_mon_thousands_sep(_Locale_monetary_t * lmon)
{ return lmon->thousands_sep[0]; }