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
struct _Locale_monetary {int dummy; } ;

/* Variables and functions */
 scalar_t__ _Locale_create (char const*,int*) ; 

struct _Locale_monetary* _Locale_monetary_create(const char *name,
                                                 struct _Locale_name_hint* hint, int *__err_code)
{ return (struct _Locale_monetary*)_Locale_create(name, __err_code); }