#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* gint64 ;
struct TYPE_6__ {int /*<<< orphan*/  modifier; int /*<<< orphan*/  id; void* size; void* mtime; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {scalar_t__ st_size; scalar_t__ st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;
typedef  TYPE_2__ ChangeSetDirent ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ce_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
update_file (ChangeSetDirent *dent,
             unsigned char *sha1,
             SeafStat *st,
             const char *modifier)
{
    if (!sha1 || !st || !S_ISREG(st->st_mode))
        return;
    dent->mode = create_ce_mode(st->st_mode);
    dent->mtime = (gint64)st->st_mtime;
    dent->size = (gint64)st->st_size;
    rawdata_to_hex (sha1, dent->id, 20);

    g_free (dent->modifier);
    dent->modifier = g_strdup(modifier);
}