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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int rtp_seq; int /*<<< orphan*/  rtp_roc; } ;
typedef  TYPE_1__ srtp_session_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
srtp_compute_roc (const srtp_session_t *s, uint16_t seq)
{
    uint32_t roc = s->rtp_roc;

    if (((seq - s->rtp_seq) & 0xffff) < 0x8000)
    {
        /* Sequence is ahead, good */
        if (seq < s->rtp_seq)
            roc++; /* Sequence number wrap */
    }
    else
    {
        /* Sequence is late, bad */
        if (seq > s->rtp_seq)
            roc--; /* Wrap back */
    }
    return roc;
}