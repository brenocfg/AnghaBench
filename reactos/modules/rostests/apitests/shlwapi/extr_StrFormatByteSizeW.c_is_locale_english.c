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
typedef  scalar_t__ LANGID ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetUserDefaultLangID () ; 
 scalar_t__ LANG_DUTCH ; 
 scalar_t__ LANG_ENGLISH ; 
 scalar_t__ PRIMARYLANGID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL is_locale_english(void)
{
    /* Surprisingly GetThreadLocale() is irrelevant here */
    LANGID langid = PRIMARYLANGID(GetUserDefaultLangID());
    /* With the checks in DO_TEST, DUTCH can be used here as well.
    TODO: Add other combinations that should work. */
    return langid == LANG_ENGLISH || langid == LANG_DUTCH;
}