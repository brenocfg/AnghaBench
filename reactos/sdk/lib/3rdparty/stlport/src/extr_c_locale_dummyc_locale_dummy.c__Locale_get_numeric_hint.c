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
struct _Locale_name_hint {int dummy; } ;

/* Variables and functions */

struct _Locale_name_hint* _Locale_get_numeric_hint(struct _Locale_numeric* numeric)
{ return 0; }