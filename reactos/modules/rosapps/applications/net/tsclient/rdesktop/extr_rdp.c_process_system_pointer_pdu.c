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
typedef  int uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
#define  RDP_NULL_POINTER 128 
 int /*<<< orphan*/  in_uint16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_set_null_cursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
process_system_pointer_pdu(RDPCLIENT * This, STREAM s)
{
	uint16 system_pointer_type;

	in_uint16(s, system_pointer_type);
	switch (system_pointer_type)
	{
		case RDP_NULL_POINTER:
			ui_set_null_cursor(This);
			break;

		default:
			unimpl("System pointer message 0x%x\n", system_pointer_type);
	}
}