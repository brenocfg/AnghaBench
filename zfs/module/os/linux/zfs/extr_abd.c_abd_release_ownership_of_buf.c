#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int abd_flags; scalar_t__ abd_size; } ;
typedef  TYPE_1__ abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABDSTAT_BUMPDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ABDSTAT_INCR (int /*<<< orphan*/ ,int) ; 
 int ABD_FLAG_META ; 
 int ABD_FLAG_OWNER ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int abd_is_linear (TYPE_1__*) ; 
 int /*<<< orphan*/  abd_is_linear_page (TYPE_1__*) ; 
 int /*<<< orphan*/  abd_verify (TYPE_1__*) ; 
 int /*<<< orphan*/  abdstat_linear_cnt ; 
 int /*<<< orphan*/  abdstat_linear_data_size ; 

void
abd_release_ownership_of_buf(abd_t *abd)
{
	ASSERT(abd_is_linear(abd));
	ASSERT(abd->abd_flags & ABD_FLAG_OWNER);

	/*
	 * abd_free() needs to handle LINEAR_PAGE ABD's specially.
	 * Since that flag does not survive the
	 * abd_release_ownership_of_buf() -> abd_get_from_buf() ->
	 * abd_take_ownership_of_buf() sequence, we don't allow releasing
	 * these "linear but not zio_[data_]buf_alloc()'ed" ABD's.
	 */
	ASSERT(!abd_is_linear_page(abd));

	abd_verify(abd);

	abd->abd_flags &= ~ABD_FLAG_OWNER;
	/* Disable this flag since we no longer own the data buffer */
	abd->abd_flags &= ~ABD_FLAG_META;

	ABDSTAT_BUMPDOWN(abdstat_linear_cnt);
	ABDSTAT_INCR(abdstat_linear_data_size, -(int)abd->abd_size);
}