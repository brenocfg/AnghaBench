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
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ISO_PDU_DR ; 
 int /*<<< orphan*/  iso_send_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_disconnect (int /*<<< orphan*/ *) ; 

BOOL
iso_disconnect(RDPCLIENT * This)
{
	iso_send_msg(This, ISO_PDU_DR);
	return tcp_disconnect(This);
}