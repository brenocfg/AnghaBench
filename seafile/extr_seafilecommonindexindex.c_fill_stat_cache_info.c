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
struct TYPE_6__ {scalar_t__ nsec; int /*<<< orphan*/  sec; } ;
struct TYPE_5__ {scalar_t__ nsec; int /*<<< orphan*/  sec; } ;
struct cache_entry {int /*<<< orphan*/  ce_size; int /*<<< orphan*/  ce_gid; int /*<<< orphan*/  ce_uid; int /*<<< orphan*/  ce_ino; int /*<<< orphan*/  ce_dev; TYPE_2__ ce_mtime; TYPE_1__ ce_ctime; } ;
struct TYPE_7__ {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; } ;
typedef  TYPE_3__ SeafStat ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_mark_uptodate (struct cache_entry*) ; 

void fill_stat_cache_info(struct cache_entry *ce, SeafStat *st)
{
    ce->ce_ctime.sec = st->st_ctime;
    ce->ce_mtime.sec = st->st_mtime;
    ce->ce_ctime.nsec = 0;
    ce->ce_mtime.nsec = 0;
    ce->ce_dev = st->st_dev;
    ce->ce_ino = st->st_ino;
    ce->ce_uid = st->st_uid;
    ce->ce_gid = st->st_gid;
    ce->ce_size = st->st_size;

    /* if (assume_unchanged) */
    /*     ce->ce_flags |= CE_VALID; */

    if (S_ISREG(st->st_mode))
        ce_mark_uptodate(ce);
}