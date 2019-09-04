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
struct TYPE_2__ {scalar_t__ HKCUkey; scalar_t__ HKLMkey; } ;
typedef  TYPE_1__* LPSHUSKEY ;
typedef  void* HUSKEY ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ HKEY_CLASSES_ROOT ; 
 scalar_t__ HKEY_CURRENT_CONFIG ; 
 scalar_t__ HKEY_CURRENT_USER ; 
 scalar_t__ HKEY_DYN_DATA ; 
 scalar_t__ HKEY_LOCAL_MACHINE ; 
 scalar_t__ HKEY_PERFORMANCE_DATA ; 
 scalar_t__ HKEY_USERS ; 
 scalar_t__ REG_HKCU ; 

__attribute__((used)) static HKEY REG_GetHKEYFromHUSKEY(HUSKEY hUSKey, BOOL which)
{
        HKEY test = hUSKey;
        LPSHUSKEY mihk = hUSKey;

	if ((test == HKEY_CLASSES_ROOT)        ||
	    (test == HKEY_CURRENT_CONFIG)      ||
	    (test == HKEY_CURRENT_USER)        ||
	    (test == HKEY_DYN_DATA)            ||
	    (test == HKEY_LOCAL_MACHINE)       ||
	    (test == HKEY_PERFORMANCE_DATA)    ||
/* FIXME:  need to define for Win2k, ME, XP
 *	    (test == HKEY_PERFORMANCE_TEXT)    ||
 *	    (test == HKEY_PERFORMANCE_NLSTEXT) ||
 */
	    (test == HKEY_USERS)) return test;
	if (which == REG_HKCU) return mihk->HKCUkey;
	return mihk->HKLMkey;
}