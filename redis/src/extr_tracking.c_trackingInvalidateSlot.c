#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ raxIterator ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_2__ client ;

/* Variables and functions */
 int CLIENT_TRACKING ; 
 int /*<<< orphan*/ ** TrackingTable ; 
 int /*<<< orphan*/  TrackingTableUsedSlots ; 
 TYPE_2__* lookupClientByID (size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxFree (int /*<<< orphan*/ *) ; 
 scalar_t__ raxNext (TYPE_1__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxStop (TYPE_1__*) ; 
 int /*<<< orphan*/  sendTrackingMessage (TYPE_2__*,size_t) ; 

void trackingInvalidateSlot(uint64_t slot) {
    if (TrackingTable == NULL || TrackingTable[slot] == NULL) return;

    raxIterator ri;
    raxStart(&ri,TrackingTable[slot]);
    raxSeek(&ri,"^",NULL,0);
    while(raxNext(&ri)) {
        uint64_t id;
        memcpy(&id,ri.key,ri.key_len);
        client *c = lookupClientByID(id);
        if (c == NULL || !(c->flags & CLIENT_TRACKING)) continue;
        sendTrackingMessage(c,slot);
    }
    raxStop(&ri);

    /* Free the tracking table: we'll create the radix tree and populate it
     * again if more keys will be modified in this caching slot. */
    raxFree(TrackingTable[slot]);
    TrackingTable[slot] = NULL;
    TrackingTableUsedSlots--;
}