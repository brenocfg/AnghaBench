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
struct index_state {int /*<<< orphan*/  name_hash; int /*<<< orphan*/  i_name_hash; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 struct cache_entry* g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 char* g_utf8_strdown (char const*,int) ; 

struct cache_entry *index_name_exists(struct index_state *istate,
                                      const char *name, int namelen,
                                      int igncase)
{
#if defined WIN32 || defined __APPLE__
    if (!igncase)
        return g_hash_table_lookup (istate->name_hash, name);
    else {
        struct cache_entry *ce;
        char *i_name = g_utf8_strdown (name, -1);
        ce = g_hash_table_lookup (istate->i_name_hash, i_name);
        g_free (i_name);
        return ce;
    }
#else
    return g_hash_table_lookup (istate->name_hash, name);
#endif
}