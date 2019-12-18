#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  sec; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  ce_mode; TYPE_2__ ce_ctime; TYPE_1__ ce_mtime; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; } ;
typedef  TYPE_3__ SeafStat ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFDIR ; 
 int cache_entry_size (int) ; 
 struct cache_entry* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static struct cache_entry *
create_empty_dir_index_entry (const char *path, SeafStat *st)
{
    int namelen, size;
    struct cache_entry *ce;

    namelen = strlen(path);
    size = cache_entry_size(namelen);
    ce = calloc(1, size);
    memcpy(ce->name, path, namelen);
    ce->ce_flags = namelen;

    ce->ce_mtime.sec = st->st_mtime;
    ce->ce_ctime.sec = st->st_ctime;

    ce->ce_mode = S_IFDIR;
    /* sha1 is all-zero. */

    return ce;
}