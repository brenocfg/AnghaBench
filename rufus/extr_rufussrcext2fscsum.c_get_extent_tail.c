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
struct ext3_extent_tail {int dummy; } ;
struct ext3_extent_header {int dummy; } ;

/* Variables and functions */
 int EXT3_EXTENT_TAIL_OFFSET (struct ext3_extent_header*) ; 

__attribute__((used)) static struct ext3_extent_tail *get_extent_tail(struct ext3_extent_header *h)
{
	return (struct ext3_extent_tail *)(((char *)h) +
					   EXT3_EXTENT_TAIL_OFFSET(h));
}