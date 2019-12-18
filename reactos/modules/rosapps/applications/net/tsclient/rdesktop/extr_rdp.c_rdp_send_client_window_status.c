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
struct TYPE_6__ {int current_status; } ;
struct TYPE_7__ {TYPE_1__ rdp; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  RDP_DATA_PDU_CLIENT_WINDOW_STATUS ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rdp_init_data (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rdp_send_data (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ *) ; 

BOOL
rdp_send_client_window_status(RDPCLIENT * This, int status)
{
	STREAM s;

	if (This->rdp.current_status == status)
		return True;

	s = rdp_init_data(This, 12);

	if(s == NULL)
		return False;

	out_uint32_le(s, status);

	switch (status)
	{
		case 0:	/* shut the server up */
			break;

		case 1:	/* receive data again */
			out_uint32_le(s, 0);	/* unknown */
			out_uint16_le(s, This->width);
			out_uint16_le(s, This->height);
			break;
	}

	s_mark_end(s);
	This->rdp.current_status = status;
	return rdp_send_data(This, s, RDP_DATA_PDU_CLIENT_WINDOW_STATUS);
}