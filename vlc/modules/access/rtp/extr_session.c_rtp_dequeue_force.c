#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * blocks; } ;
typedef  TYPE_1__ rtp_source_t ;
struct TYPE_7__ {unsigned int srcc; TYPE_1__** srcv; } ;
typedef  TYPE_2__ rtp_session_t ;
typedef  int /*<<< orphan*/  demux_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  rtp_decode (int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_1__*) ; 

void rtp_dequeue_force (demux_t *demux, const rtp_session_t *session)
{
    for (unsigned i = 0, max = session->srcc; i < max; i++)
    {
        rtp_source_t *src = session->srcv[i];
        block_t *block;

        while (((block = src->blocks)) != NULL)
            rtp_decode (demux, session, src);
    }
}