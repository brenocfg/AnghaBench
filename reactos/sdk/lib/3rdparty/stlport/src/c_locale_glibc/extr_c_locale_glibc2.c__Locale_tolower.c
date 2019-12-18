#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _Locale_ctype {int dummy; } ;
typedef  TYPE_1__* locale_t ;
struct TYPE_2__ {int* __ctype_tolower; } ;

/* Variables and functions */

int _Locale_tolower( struct _Locale_ctype *__loc, int c )
{ return ((locale_t)__loc)->__ctype_tolower[c]; }