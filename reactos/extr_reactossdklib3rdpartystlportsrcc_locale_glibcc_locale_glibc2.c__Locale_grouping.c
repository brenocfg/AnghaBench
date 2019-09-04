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
struct _Locale_numeric {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPING ; 
 scalar_t__ _Locale_thousands_sep (struct _Locale_numeric*) ; 
 char const* _empty_str ; 
 char const* nl_langinfo_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char* _Locale_grouping(struct _Locale_numeric *__loc)
{
  return (_Locale_thousands_sep(__loc) != 0 ) ? (nl_langinfo_l(GROUPING, (locale_t)__loc)) : _empty_str;
}