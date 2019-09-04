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
struct TYPE_5__ {int offset; TYPE_1__* chunk_item; } ;
typedef  TYPE_2__ chunk ;
typedef  int UINT64 ;
typedef  int UINT16 ;
struct TYPE_4__ {int num_stripes; int type; int stripe_length; } ;

/* Variables and functions */
 int BLOCK_FLAG_RAID5 ; 
 int /*<<< orphan*/  get_raid0_offset (int,int,int,int*,int*) ; 
 int sector_align (int,int) ; 

void get_raid56_lock_range(chunk* c, UINT64 address, UINT64 length, UINT64* lockaddr, UINT64* locklen) {
    UINT64 startoff, endoff;
    UINT16 startoffstripe, endoffstripe, datastripes;

    datastripes = c->chunk_item->num_stripes - (c->chunk_item->type & BLOCK_FLAG_RAID5 ? 1 : 2);

    get_raid0_offset(address - c->offset, c->chunk_item->stripe_length, datastripes, &startoff, &startoffstripe);
    get_raid0_offset(address + length - c->offset - 1, c->chunk_item->stripe_length, datastripes, &endoff, &endoffstripe);

    startoff -= startoff % c->chunk_item->stripe_length;
    endoff = sector_align(endoff, c->chunk_item->stripe_length);

    *lockaddr = c->offset + (startoff * datastripes);
    *locklen = (endoff - startoff) * datastripes;
}