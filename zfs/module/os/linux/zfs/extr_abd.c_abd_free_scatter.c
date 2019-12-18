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
struct TYPE_5__ {scalar_t__ abd_size; int /*<<< orphan*/  abd_children; } ;
typedef  TYPE_1__ abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABDSTAT_BUMPDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ABDSTAT_INCR (int /*<<< orphan*/ ,int) ; 
 scalar_t__ P2ROUNDUP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGESIZE ; 
 int /*<<< orphan*/  abd_free_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  abd_free_struct (TYPE_1__*) ; 
 int /*<<< orphan*/  abdstat_scatter_chunk_waste ; 
 int /*<<< orphan*/  abdstat_scatter_cnt ; 
 int /*<<< orphan*/  abdstat_scatter_data_size ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
abd_free_scatter(abd_t *abd)
{
	abd_free_pages(abd);

	zfs_refcount_destroy(&abd->abd_children);
	ABDSTAT_BUMPDOWN(abdstat_scatter_cnt);
	ABDSTAT_INCR(abdstat_scatter_data_size, -(int)abd->abd_size);
	ABDSTAT_INCR(abdstat_scatter_chunk_waste,
	    (int)abd->abd_size - (int)P2ROUNDUP(abd->abd_size, PAGESIZE));

	abd_free_struct(abd);
}