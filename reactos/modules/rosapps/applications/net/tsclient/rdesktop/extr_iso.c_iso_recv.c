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
typedef  int uint8 ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int ISO_PDU_DT ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/ * iso_recv_msg (int /*<<< orphan*/ *,int*,int*) ; 

STREAM
iso_recv(RDPCLIENT * This, uint8 * rdpver)
{
	STREAM s;
	uint8 code = 0;

	s = iso_recv_msg(This, &code, rdpver);
	if (s == NULL)
		return NULL;
	if (rdpver != NULL)
		if (*rdpver != 3)
			return s;
	if (code != ISO_PDU_DT)
	{
		error("expected DT, got 0x%x\n", code);
		return NULL;
	}
	return s;
}