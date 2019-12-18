#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * channel_hdr; int /*<<< orphan*/ * rdp_hdr; int /*<<< orphan*/ * sec_hdr; int /*<<< orphan*/ * mcs_hdr; int /*<<< orphan*/ * iso_hdr; scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; } ;
struct TYPE_6__ {int /*<<< orphan*/ * channel_hdr; int /*<<< orphan*/ * rdp_hdr; int /*<<< orphan*/ * sec_hdr; int /*<<< orphan*/ * mcs_hdr; int /*<<< orphan*/ * iso_hdr; scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; } ;
struct TYPE_8__ {int sock; TYPE_2__ out; TYPE_1__ in; } ;
struct TYPE_9__ {TYPE_3__ tcp; } ;
typedef  TYPE_4__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
tcp_reset_state(RDPCLIENT * This)
{
	This->tcp.sock = -1;		/* reset socket */

	/* Clear the incoming stream */
	if (This->tcp.in.data != NULL)
		free(This->tcp.in.data);
	This->tcp.in.p = NULL;
	This->tcp.in.end = NULL;
	This->tcp.in.data = NULL;
	This->tcp.in.size = 0;
	This->tcp.in.iso_hdr = NULL;
	This->tcp.in.mcs_hdr = NULL;
	This->tcp.in.sec_hdr = NULL;
	This->tcp.in.rdp_hdr = NULL;
	This->tcp.in.channel_hdr = NULL;

	/* Clear the outgoing stream */
	if (This->tcp.out.data != NULL)
		free(This->tcp.out.data);
	This->tcp.out.p = NULL;
	This->tcp.out.end = NULL;
	This->tcp.out.data = NULL;
	This->tcp.out.size = 0;
	This->tcp.out.iso_hdr = NULL;
	This->tcp.out.mcs_hdr = NULL;
	This->tcp.out.sec_hdr = NULL;
	This->tcp.out.rdp_hdr = NULL;
	This->tcp.out.channel_hdr = NULL;
}