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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int payload_type; int (* mcb ) (void*,struct RTPMessage*) ;void* cs; int /*<<< orphan*/ * bwc; int /*<<< orphan*/  friend_number; void* m; int /*<<< orphan*/  ssrc; } ;
typedef  TYPE_1__ RTPSession ;
typedef  void Messenger ;
typedef  int /*<<< orphan*/  BWController ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 int /*<<< orphan*/  assert (void*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  random_int () ; 
 int rtp_allow_receiving (TYPE_1__*) ; 

RTPSession *rtp_new (int payload_type, Messenger *m, uint32_t friendnumber,
                     BWController *bwc, void *cs,
                     int (*mcb) (void *, struct RTPMessage *))
{
    assert(mcb);
    assert(cs);
    assert(m);

    RTPSession *retu = calloc(1, sizeof(RTPSession));

    if (!retu) {
        LOGGER_WARNING("Alloc failed! Program might misbehave!");
        return NULL;
    }

    retu->ssrc = random_int();
    retu->payload_type = payload_type;

    retu->m = m;
    retu->friend_number = friendnumber;

    /* Also set payload type as prefix */

    retu->bwc = bwc;
    retu->cs = cs;
    retu->mcb = mcb;

    if (-1 == rtp_allow_receiving(retu)) {
        LOGGER_WARNING("Failed to start rtp receiving mode");
        free(retu);
        return NULL;
    }

    return retu;
}