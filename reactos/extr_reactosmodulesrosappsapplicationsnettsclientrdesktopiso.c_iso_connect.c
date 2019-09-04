#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ ISO_PDU_CC ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/ * iso_recv_msg (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iso_send_connection_request (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tcp_connect (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tcp_disconnect (int /*<<< orphan*/ *) ; 

BOOL
iso_connect(RDPCLIENT * This, char *server, char *cookie)
{
	uint8 code = 0;

	if (!tcp_connect(This, server))
		return False;

	if (!iso_send_connection_request(This, cookie))
		return False;

	if (iso_recv_msg(This, &code, NULL) == NULL)
		return False;

	if (code != ISO_PDU_CC)
	{
		error("expected CC, got 0x%x\n", code);
		tcp_disconnect(This);
		return False;
	}

	return True;
}