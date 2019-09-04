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
typedef  int /*<<< orphan*/  nsresult ;

/* Variables and functions */
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cat_mgr ; 
 int /*<<< orphan*/  nsICategoryManager_GetCategoryEntry (int /*<<< orphan*/ ,char const*,char const*,char**) ; 

char *get_nscategory_entry(const char *category, const char *entry)
{
    char *ret = NULL;
    nsresult nsres;

    nsres = nsICategoryManager_GetCategoryEntry(cat_mgr, category, entry, &ret);
    return NS_SUCCEEDED(nsres) ? ret : NULL;
}