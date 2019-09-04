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
typedef  int /*<<< orphan*/  _Locale_lcid_t ;
struct TYPE_3__ {int /*<<< orphan*/  lc; } ;
typedef  TYPE_1__ _Locale_ctype_t ;

/* Variables and functions */

_Locale_lcid_t* _Locale_get_ctype_hint(_Locale_ctype_t* ltype)
{ return (ltype != 0) ? &ltype->lc : 0; }