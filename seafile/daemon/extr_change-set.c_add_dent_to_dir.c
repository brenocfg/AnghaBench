#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dents_i; int /*<<< orphan*/  dents; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ChangeSetDirent ;
typedef  TYPE_2__ ChangeSetDir ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_utf8_strdown (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
add_dent_to_dir (ChangeSetDir *dir, ChangeSetDirent *dent)
{
    g_hash_table_insert (dir->dents,
                         g_strdup(dent->name),
                         dent);
#if defined WIN32 || defined __APPLE__
    g_hash_table_insert (dir->dents_i,
                         g_utf8_strdown(dent->name, -1),
                         dent);
#endif
}