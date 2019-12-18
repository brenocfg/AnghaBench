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
struct TYPE_6__ {unsigned int srcc; struct TYPE_6__* ptv; struct TYPE_6__* srcv; } ;
typedef  TYPE_1__ rtp_session_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  rtp_source_destroy (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__) ; 

void rtp_session_destroy (demux_t *demux, rtp_session_t *session)
{
    for (unsigned i = 0; i < session->srcc; i++)
        rtp_source_destroy (demux, session, session->srcv[i]);

    free (session->srcv);
    free (session->ptv);
    free (session);
    (void)demux;
}