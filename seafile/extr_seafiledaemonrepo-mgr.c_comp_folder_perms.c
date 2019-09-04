#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint ;
typedef  TYPE_1__* gconstpointer ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ FolderPerm ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gint
comp_folder_perms (gconstpointer a, gconstpointer b)
{
    const FolderPerm *perm_a = a, *perm_b = b;

    return (strcmp (perm_b->path, perm_a->path));
}