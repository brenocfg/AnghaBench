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
typedef  int /*<<< orphan*/  ddt_t ;
typedef  int /*<<< orphan*/  ddt_entry_t ;

/* Variables and functions */
 void* ddt_cache ; 
 void* ddt_entry_cache ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ddt_init(void)
{
	ddt_cache = kmem_cache_create("ddt_cache",
	    sizeof (ddt_t), 0, NULL, NULL, NULL, NULL, NULL, 0);
	ddt_entry_cache = kmem_cache_create("ddt_entry_cache",
	    sizeof (ddt_entry_t), 0, NULL, NULL, NULL, NULL, NULL, 0);
}