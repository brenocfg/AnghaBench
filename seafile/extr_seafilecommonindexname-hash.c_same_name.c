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
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_name_compare (char const*,int,int /*<<< orphan*/ ,int) ; 
 int ce_namelen (struct cache_entry const*) ; 

__attribute__((used)) static int same_name(const struct cache_entry *ce, const char *name, int namelen, int icase)
{
    int len = ce_namelen(ce);

    /*
     * Always do exact compare, even if we want a case-ignoring comparison;
     * we do the quick exact one first, because it will be the common case.
     */
    if (len == namelen && !cache_name_compare(name, namelen, ce->name, len))
        return 1;
    else
        return 0;

    /* if (!icase) */
    /*  return 0; */

    /*
     * If the entry we're comparing is a filename (no trailing slash), then compare
     * the lengths exactly.
     */
    /* if (name[namelen - 1] != '/') */
    /*  return slow_same_name(name, namelen, ce->name, len); */

    /*
     * For a directory, we point to an arbitrary cache_entry filename.  Just
     * make sure the directory portion matches.
     */
    /* return slow_same_name(name, namelen, ce->name, namelen < len ? namelen : len); */
}