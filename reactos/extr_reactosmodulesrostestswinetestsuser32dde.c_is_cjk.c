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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetUserDefaultLangID () ; 
 int LANG_CHINESE ; 
 int LANG_JAPANESE ; 
 int LANG_KOREAN ; 
 int PRIMARYLANGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL is_cjk(void)
{
    int lang_id = PRIMARYLANGID(GetUserDefaultLangID());

    if (lang_id == LANG_CHINESE || lang_id == LANG_JAPANESE || lang_id == LANG_KOREAN)
        return TRUE;
    return FALSE;
}