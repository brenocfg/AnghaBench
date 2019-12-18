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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_3__ {int /*<<< orphan*/  wd_to_path; } ;
typedef  TYPE_1__ WatchPathMapping ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 

__attribute__((used)) static void add_mapping (WatchPathMapping *mapping,
                         const char *path,
                         int wd)
{
    g_hash_table_insert (mapping->wd_to_path, (gpointer)(long)wd, g_strdup(path));
}