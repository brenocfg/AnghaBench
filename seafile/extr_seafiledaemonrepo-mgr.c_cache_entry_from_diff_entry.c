#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sec; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  ce_mode; TYPE_1__ ce_mtime; int /*<<< orphan*/  ce_size; int /*<<< orphan*/  modifier; int /*<<< orphan*/  sha1; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; int /*<<< orphan*/  modifier; int /*<<< orphan*/  sha1; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ DiffEntry ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFDIR ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int cache_entry_size (int) ; 
 struct cache_entry* calloc (int,int) ; 
 int /*<<< orphan*/  create_ce_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cache_entry *
cache_entry_from_diff_entry (DiffEntry *de)
{
    int size, namelen;
    struct cache_entry *ce;

    namelen = strlen(de->name);
    size = cache_entry_size(namelen);
    ce = calloc(1, size);
    memcpy(ce->name, de->name, namelen);
    ce->ce_flags = namelen;

    memcpy (ce->sha1, de->sha1, 20);
    ce->modifier = g_strdup(de->modifier);
    ce->ce_size = de->size;
    ce->ce_mtime.sec = de->mtime;

    if (S_ISREG(de->mode))
        ce->ce_mode = create_ce_mode (de->mode);
    else
        ce->ce_mode = S_IFDIR;

    return ce;
}