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
struct TYPE_4__ {int /*<<< orphan*/  locked_files; } ;
typedef  TYPE_1__ LockedFileSet ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 

void
locked_file_set_free (LockedFileSet *fset)
{
    if (!fset)
        return;
    g_hash_table_destroy (fset->locked_files);
    g_free (fset);
}