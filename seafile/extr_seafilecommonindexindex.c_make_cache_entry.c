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
struct cache_entry {int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  sha1; } ;

/* Variables and functions */
 int cache_entry_size (int) ; 
 struct cache_entry* calloc (int,int) ; 
 int /*<<< orphan*/  create_ce_flags (int,int) ; 
 int /*<<< orphan*/  create_ce_mode (unsigned int) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct cache_entry* refresh_cache_entry (struct cache_entry*,char const*) ; 
 int strlen (char const*) ; 

struct cache_entry *make_cache_entry(unsigned int mode,
                                     const unsigned char *sha1, 
                                     const char *path, const char *full_path, 
                                     int stage, int refresh)
{
    int size, len;
    struct cache_entry *ce;

    /* if (!verify_path(path)) { */
    /*     seaf_warning("Invalid path '%s'", path); */
    /*     return NULL; */
    /* } */

    len = strlen(path);
    size = cache_entry_size(len);
    ce = calloc(1, size);

    hashcpy(ce->sha1, sha1);
    memcpy(ce->name, path, len);
    ce->ce_flags = create_ce_flags(len, stage);
    ce->ce_mode = create_ce_mode(mode);

    if (refresh)
        return refresh_cache_entry(ce, full_path);

    return ce;
}