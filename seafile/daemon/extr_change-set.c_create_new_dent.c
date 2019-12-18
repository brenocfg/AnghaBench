#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;
typedef  TYPE_2__ ChangeSetDirent ;
typedef  int /*<<< orphan*/  ChangeSetDir ;

/* Variables and functions */
 int /*<<< orphan*/  add_dent_to_dir (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* changeset_dirent_new (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ce_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,char*,int) ; 

__attribute__((used)) static void
create_new_dent (ChangeSetDir *dir,
                 const char *dname,
                 unsigned char *sha1,
                 SeafStat *st,
                 const char *modifier,
                 ChangeSetDirent *in_new_dent)
{
    if (in_new_dent) {
        g_free (in_new_dent->name);
        in_new_dent->name = g_strdup(dname);
        add_dent_to_dir (dir, in_new_dent);
        return;
    }

    char id[41];
    rawdata_to_hex (sha1, id, 20);
    ChangeSetDirent *new_dent;
    new_dent = changeset_dirent_new (id, create_ce_mode(st->st_mode), dname,
                                     st->st_mtime, modifier, st->st_size);

    add_dent_to_dir (dir, new_dent);
}