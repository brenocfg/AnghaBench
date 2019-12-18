#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  cp; TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_numeric_t ;

/* Variables and functions */
 char const* __GetLocaleName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

char const* _Locale_numeric_name(const _Locale_numeric_t* lnum, char* buf)
{ return __GetLocaleName(lnum->lc.id, lnum->cp, buf); }