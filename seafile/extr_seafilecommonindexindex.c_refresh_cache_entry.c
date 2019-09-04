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
struct cache_entry {int dummy; } ;
typedef  int /*<<< orphan*/  SeafStat ;

/* Variables and functions */
 int /*<<< orphan*/  fill_stat_cache_info (struct cache_entry*,int /*<<< orphan*/ *) ; 
 scalar_t__ seaf_stat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 

__attribute__((used)) static struct cache_entry *refresh_cache_entry(struct cache_entry *ce,
                                               const char *full_path)
{
    SeafStat st;

    if (seaf_stat (full_path, &st) < 0) {
        seaf_warning("Failed to stat %s.\n", full_path);
        return NULL;
    }
    fill_stat_cache_info(ce, &st);

    return ce;
}