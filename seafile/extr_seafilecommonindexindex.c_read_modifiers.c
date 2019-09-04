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
struct index_state {unsigned int cache_nr; int has_modifier; TYPE_1__** cache; } ;
struct TYPE_2__ {char* modifier; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 char* g_strndup (char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

__attribute__((used)) static int read_modifiers (struct index_state *istate, void *data, unsigned int size)
{
    char *p = data, *sep = data, *modifier;
    unsigned int i;
    unsigned int idx = 0;

    for (i = 0; i < size; ++i) {
        if (*sep == '\n') {
            while (idx < istate->cache_nr &&
                   S_ISDIR(istate->cache[idx]->ce_mode))
                ++idx;
            if (idx >= istate->cache_nr) {
                seaf_warning ("More modifiers than cache entries.\n");
                return -1;
            }

            modifier = g_strndup(p, sep - p);
            istate->cache[idx]->modifier = modifier;
            idx++;
            p = sep + 1;
        }
        ++sep;
    }

    while (idx < istate->cache_nr &&
           S_ISDIR(istate->cache[idx]->ce_mode))
        ++idx;

    if (idx != istate->cache_nr) {
        seaf_warning ("Less modifiers than cached entries.\n");
        return -1;
    }

    istate->has_modifier = 1;

    return 0;
}