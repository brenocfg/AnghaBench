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
struct index_state {int /*<<< orphan*/  name_hash; } ;
struct cache_entry {int ce_flags; struct cache_entry* next; } ;

/* Variables and functions */
 int CE_UNHASHED ; 
 unsigned int hash_name (char const*,int) ; 
 int /*<<< orphan*/  lazy_init_name_hash (struct index_state*) ; 
 struct cache_entry* lookup_hash (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ same_name (struct cache_entry*,char const*,int,int) ; 

struct cache_entry *index_name_exists(struct index_state *istate, const char *name, int namelen, int icase)
{
    unsigned int hash = hash_name(name, namelen);
    struct cache_entry *ce;

    lazy_init_name_hash(istate);
    ce = lookup_hash(hash, &istate->name_hash);

    while (ce) {
        if (!(ce->ce_flags & CE_UNHASHED)) {
            if (same_name(ce, name, namelen, icase))
                return ce;
        }
        ce = ce->next;
    }

    /*
     * Might be a submodule.  Despite submodules being directories,
     * they are stored in the name hash without a closing slash.
     * When ignore_case is 1, directories are stored in the name hash
     * with their closing slash.
     *
     * The side effect of this storage technique is we have need to
     * remove the slash from name and perform the lookup again without
     * the slash.  If a match is made, S_ISGITLINK(ce->mode) will be
     * true.
     */
    /* if (icase && name[namelen - 1] == '/') { */
    /*  ce = index_name_exists(istate, name, namelen - 1, icase); */
    /*  if (ce && S_ISGITLINK(ce->ce_mode)) */
    /*      return ce; */
    /* } */
    return NULL;
}