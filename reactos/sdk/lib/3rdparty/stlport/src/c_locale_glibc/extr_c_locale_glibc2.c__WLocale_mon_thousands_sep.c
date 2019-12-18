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
struct _Locale_monetary {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _Locale_mon_thousands_sep (struct _Locale_monetary*) ; 

wchar_t _WLocale_mon_thousands_sep(struct _Locale_monetary * __loc)
{ return (wchar_t)_Locale_mon_thousands_sep(__loc); }