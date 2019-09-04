#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* chunk_item; } ;
typedef  TYPE_2__ chunk ;
typedef  int UINT64 ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 int BLOCK_FLAG_DUPLICATE ; 
 int BLOCK_FLAG_RAID0 ; 
 int BLOCK_FLAG_RAID1 ; 
 int BLOCK_FLAG_RAID10 ; 
 int BLOCK_FLAG_RAID5 ; 
 int BLOCK_FLAG_RAID6 ; 
 int BLOCK_FLAG_SINGLE ; 

__attribute__((used)) static __inline UINT64 get_chunk_dup_type(chunk* c) {
    if (c->chunk_item->type & BLOCK_FLAG_RAID0)
        return BLOCK_FLAG_RAID0;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID1)
        return BLOCK_FLAG_RAID1;
    else if (c->chunk_item->type & BLOCK_FLAG_DUPLICATE)
        return BLOCK_FLAG_DUPLICATE;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID10)
        return BLOCK_FLAG_RAID10;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID5)
        return BLOCK_FLAG_RAID5;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID6)
        return BLOCK_FLAG_RAID6;
    else
        return BLOCK_FLAG_SINGLE;
}