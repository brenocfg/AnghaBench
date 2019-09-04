#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* locinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lc_handle; int /*<<< orphan*/  mb_cur_max; int /*<<< orphan*/  lc_collate_cp; int /*<<< orphan*/  lc_codepage; } ;

/* Variables and functions */
 unsigned int LC_MAX ; 
 unsigned int LC_MIN ; 
 int /*<<< orphan*/  LOCK_LOCALE ; 
 int /*<<< orphan*/  MSVCRT___lc_collate_cp ; 
 int /*<<< orphan*/ * MSVCRT___lc_handle ; 
 scalar_t__ MSVCRT__create_locale (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* MSVCRT_locale ; 
 int /*<<< orphan*/  UNLOCK_LOCALE ; 
 int /*<<< orphan*/  _MB_CP_ANSI ; 
 int /*<<< orphan*/  __lc_codepage ; 
 int /*<<< orphan*/  __mb_cur_max ; 
 int /*<<< orphan*/  _setmbcp (int /*<<< orphan*/ ) ; 
 scalar_t__ global_locale ; 

void __init_global_locale()
{
    unsigned i;

    LOCK_LOCALE;
    /* Someone created it before us */
    if(global_locale)
        return;
    global_locale = MSVCRT__create_locale(0, "C");

    __lc_codepage = MSVCRT_locale->locinfo->lc_codepage;
    MSVCRT___lc_collate_cp = MSVCRT_locale->locinfo->lc_collate_cp;
    __mb_cur_max = MSVCRT_locale->locinfo->mb_cur_max;
    for(i=LC_MIN; i<=LC_MAX; i++)
        MSVCRT___lc_handle[i] = MSVCRT_locale->locinfo->lc_handle[i];
    _setmbcp(_MB_CP_ANSI);
    UNLOCK_LOCALE;
}