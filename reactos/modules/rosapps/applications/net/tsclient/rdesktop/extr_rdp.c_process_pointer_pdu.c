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
#define  RDP_POINTER_CACHED 131 
#define  RDP_POINTER_COLOR 130 
#define  RDP_POINTER_MOVE 129 
#define  RDP_POINTER_SYSTEM 128 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_cached_pointer_pdu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_colour_pointer_pdu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_system_pointer_pdu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_move_pointer (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

__attribute__((used)) static void
process_pointer_pdu(RDPCLIENT * This, STREAM s)
{
	uint16 message_type;
	uint16 x, y;

	in_uint16_le(s, message_type);
	in_uint8s(s, 2);	/* pad */

	switch (message_type)
	{
		case RDP_POINTER_MOVE:
			in_uint16_le(s, x);
			in_uint16_le(s, y);
			if (s_check(s))
				ui_move_pointer(This, x, y);
			break;

		case RDP_POINTER_COLOR:
			process_colour_pointer_pdu(This, s);
			break;

		case RDP_POINTER_CACHED:
			process_cached_pointer_pdu(This, s);
			break;

		case RDP_POINTER_SYSTEM:
			process_system_pointer_pdu(This, s);
			break;

		default:
			unimpl("Pointer message 0x%x\n", message_type);
	}
}