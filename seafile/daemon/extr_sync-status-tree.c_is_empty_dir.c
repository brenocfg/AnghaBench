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
typedef  int gboolean ;
struct TYPE_5__ {TYPE_1__* subdir; } ;
struct TYPE_4__ {int /*<<< orphan*/  dirents; } ;
typedef  TYPE_2__ SyncStatusDirent ;

/* Variables and functions */
 scalar_t__ g_hash_table_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static gboolean
is_empty_dir (SyncStatusDirent *dirent)
{
    return (g_hash_table_size(dirent->subdir->dirents) == 0);
}