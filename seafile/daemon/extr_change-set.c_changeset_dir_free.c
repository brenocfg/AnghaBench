#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dents_i; int /*<<< orphan*/  dents; } ;
typedef  TYPE_1__ ChangeSetDir ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
changeset_dir_free (ChangeSetDir *dir)
{
    if (!dir)
        return;
    g_hash_table_destroy (dir->dents);
#if defined WIN32 || defined __APPLE__
    g_hash_table_destroy (dir->dents_i);
#endif
    g_free (dir);
}