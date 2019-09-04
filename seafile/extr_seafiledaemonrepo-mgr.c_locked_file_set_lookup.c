#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  locked_files; } ;
typedef  TYPE_1__ LockedFileSet ;
typedef  int /*<<< orphan*/  LockedFile ;

/* Variables and functions */
 scalar_t__ g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 

LockedFile *
locked_file_set_lookup (LockedFileSet *fset, const char *path)
{
    return (LockedFile *) g_hash_table_lookup (fset->locked_files, path);
}