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
typedef  int /*<<< orphan*/  sa_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_cache ; 
 int /*<<< orphan*/  sa_cache_constructor ; 
 int /*<<< orphan*/  sa_cache_destructor ; 

void
sa_cache_init(void)
{
	sa_cache = kmem_cache_create("sa_cache",
	    sizeof (sa_handle_t), 0, sa_cache_constructor,
	    sa_cache_destructor, NULL, NULL, NULL, 0);
}