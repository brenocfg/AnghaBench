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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct buffer_head* get_block_bh_pin (struct block_device*,int /*<<< orphan*/ ,unsigned long,int) ; 

struct buffer_head *
get_block_bh(
    struct block_device *   bdev,
    sector_t                block,
    unsigned long           size,
    int                     zero
) 
{
    return get_block_bh_pin(bdev, block, size, zero);
}