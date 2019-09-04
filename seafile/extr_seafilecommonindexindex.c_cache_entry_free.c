#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cache_entry {int /*<<< orphan*/  modifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cache_entry*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 

void cache_entry_free (struct cache_entry *ce)
{
    g_free (ce->modifier);
    free (ce);
}