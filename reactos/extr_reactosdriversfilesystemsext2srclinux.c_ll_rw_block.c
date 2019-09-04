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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int SWRITE ; 
 int WRITE ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int,struct buffer_head*) ; 
 scalar_t__ test_clear_buffer_dirty (struct buffer_head*) ; 
 scalar_t__ test_set_buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void ll_rw_block(int rw, int nr, struct buffer_head * bhs[])
{
    int i;

    for (i = 0; i < nr; i++) {

        struct buffer_head *bh = bhs[i];

        if (rw == SWRITE)
            lock_buffer(bh);
        else if (test_set_buffer_locked(bh))
            continue;

        if (rw == WRITE || rw == SWRITE) {
            if (test_clear_buffer_dirty(bh)) {
                get_bh(bh);
                submit_bh(WRITE, bh);
                continue;
            }
        } else {
            if (!buffer_uptodate(bh)) {
                get_bh(bh);
                submit_bh(rw, bh);
                continue;
            }
        }
        unlock_buffer(bh);
    }
}