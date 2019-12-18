#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rtp; int /*<<< orphan*/  rtcp; } ;
typedef  TYPE_1__ srtp_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  proto_destroy (int /*<<< orphan*/ *) ; 

void srtp_destroy (srtp_session_t *s)
{
    assert (s != NULL);

    proto_destroy (&s->rtcp);
    proto_destroy (&s->rtp);
    free (s);
}