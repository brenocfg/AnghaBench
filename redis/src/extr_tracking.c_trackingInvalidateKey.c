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
typedef  int uint64_t ;
typedef  scalar_t__ sds ;
struct TYPE_3__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int TRACKING_TABLE_SIZE ; 
 int /*<<< orphan*/ * TrackingTable ; 
 scalar_t__ TrackingTableUsedSlots ; 
 int crc64 (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 int /*<<< orphan*/  trackingInvalidateSlot (int) ; 

void trackingInvalidateKey(robj *keyobj) {
    if (TrackingTable == NULL || TrackingTableUsedSlots == 0) return;

    sds sdskey = keyobj->ptr;
    uint64_t hash = crc64(0,
        (unsigned char*)sdskey,sdslen(sdskey))&(TRACKING_TABLE_SIZE-1);
    trackingInvalidateSlot(hash);
}