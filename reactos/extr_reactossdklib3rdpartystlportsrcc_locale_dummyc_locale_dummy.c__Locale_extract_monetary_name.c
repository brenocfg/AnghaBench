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
struct _Locale_name_hint {int dummy; } ;

/* Variables and functions */
 char const* _Locale_extract_name (char const*,int*) ; 

char const* _Locale_extract_monetary_name(const char *name, char *buf,
                                          struct _Locale_name_hint* hint, int *__err_code)
{ return _Locale_extract_name(name, __err_code); }