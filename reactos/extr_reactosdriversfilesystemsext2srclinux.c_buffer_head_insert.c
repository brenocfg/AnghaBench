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
struct buffer_head {int /*<<< orphan*/  b_rb_node; } ;
struct block_device {int /*<<< orphan*/  bd_bh_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_head_blocknr_cmp ; 
 int /*<<< orphan*/  rb_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buffer_head_insert(struct block_device *bdev, struct buffer_head *bh)
{
    rb_insert(&bdev->bd_bh_root, &bh->b_rb_node, buffer_head_blocknr_cmp);
}