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
struct TYPE_4__ {int /*<<< orphan*/ * ptv; scalar_t__ ptc; scalar_t__ srcc; int /*<<< orphan*/ * srcv; } ;
typedef  TYPE_1__ rtp_session_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

rtp_session_t *
rtp_session_create (demux_t *demux)
{
    rtp_session_t *session = malloc (sizeof (*session));
    if (session == NULL)
        return NULL;

    session->srcv = NULL;
    session->srcc = 0;
    session->ptc = 0;
    session->ptv = NULL;

    (void)demux;
    return session;
}