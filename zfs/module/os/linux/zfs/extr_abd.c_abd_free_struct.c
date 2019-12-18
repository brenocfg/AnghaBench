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
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABDSTAT_INCR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  abd_cache ; 
 int /*<<< orphan*/  abdstat_struct_size ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
abd_free_struct(abd_t *abd)
{
	kmem_cache_free(abd_cache, abd);
	ABDSTAT_INCR(abdstat_struct_size, -(int)sizeof (abd_t));
}