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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ rtp_rcc; } ;
typedef  TYPE_1__ srtp_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void srtp_setrcc_rate (srtp_session_t *s, uint16_t rate)
{
    assert (rate != 0);
    s->rtp_rcc = rate;
}