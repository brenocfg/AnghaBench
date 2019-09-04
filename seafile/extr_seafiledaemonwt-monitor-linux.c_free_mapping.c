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
struct TYPE_4__ {int /*<<< orphan*/  wd_to_path; } ;
typedef  TYPE_1__ WatchPathMapping ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_mapping (WatchPathMapping *mapping)
{
    g_hash_table_destroy (mapping->wd_to_path);
    g_free (mapping);
}