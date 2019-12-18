#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned int num_channels; scalar_t__ mcs_userid; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ MCS_GLOBAL_CHANNEL ; 
 scalar_t__ MCS_USERCHANNEL_BASE ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  iso_connect (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  iso_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  mcs_recv_aucf (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  mcs_recv_cjcf (TYPE_1__*) ; 
 int /*<<< orphan*/  mcs_recv_connect_response (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs_send_aurq (TYPE_1__*) ; 
 int /*<<< orphan*/  mcs_send_cjrq (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mcs_send_connect_initial (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs_send_edrq (TYPE_1__*) ; 

BOOL
mcs_connect(RDPCLIENT * This, char *server, char * cookie, STREAM mcs_data)
{
	unsigned int i;

	if (!iso_connect(This, server, cookie))
		return False;

	if (!mcs_send_connect_initial(This, mcs_data) || !mcs_recv_connect_response(This, mcs_data))
		goto error;

	if (!mcs_send_edrq(This) || !mcs_send_aurq(This))
		goto error;

	if (!mcs_recv_aucf(This, &This->mcs_userid))
		goto error;

	if (!mcs_send_cjrq(This, This->mcs_userid + MCS_USERCHANNEL_BASE) || !mcs_recv_cjcf(This))
		goto error;

	if (!mcs_send_cjrq(This, MCS_GLOBAL_CHANNEL) || !mcs_recv_cjcf(This))
		goto error;

	for (i = 0; i < This->num_channels; i++)
	{
		if (!mcs_send_cjrq(This, MCS_GLOBAL_CHANNEL + 1 + i) || !mcs_recv_cjcf(This))
			goto error;
	}
	return True;

	error:
	iso_disconnect(This);
	return False;
}