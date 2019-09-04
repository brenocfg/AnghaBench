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
#define  RDP_UPDATE_BITMAP 131 
#define  RDP_UPDATE_ORDERS 130 
#define  RDP_UPDATE_PALETTE 129 
#define  RDP_UPDATE_SYNCHRONIZE 128 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_bitmap_updates (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_orders (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_palette (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_begin_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_end_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

__attribute__((used)) static void
process_update_pdu(RDPCLIENT * This, STREAM s)
{
	uint16 update_type, count;

	in_uint16_le(s, update_type);

	ui_begin_update(This);
	switch (update_type)
	{
		case RDP_UPDATE_ORDERS:
			in_uint8s(s, 2);	/* pad */
			in_uint16_le(s, count);
			in_uint8s(s, 2);	/* pad */
			process_orders(This, s, count);
			break;

		case RDP_UPDATE_BITMAP:
			process_bitmap_updates(This, s);
			break;

		case RDP_UPDATE_PALETTE:
			process_palette(This, s);
			break;

		case RDP_UPDATE_SYNCHRONIZE:
			break;

		default:
			unimpl("update %d\n", update_type);
	}
	ui_end_update(This);
}