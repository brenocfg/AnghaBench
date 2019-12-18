#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* zb_blkid; scalar_t__ zb_level; void* zb_object; } ;
typedef  TYPE_1__ zbookmark_phys_t ;
typedef  void* uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline void
create_zbookmark_from_obj_off(zbookmark_phys_t *zb, uint64_t object,
    uint64_t blkid)
{
	zb->zb_object = object;
	zb->zb_level = 0;
	zb->zb_blkid = blkid;
}