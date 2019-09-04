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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLIPRDR_DATA_REQUEST ; 
 int /*<<< orphan*/  CLIPRDR_REQUEST ; 
 int /*<<< orphan*/  DEBUG_CLIPBOARD (char*) ; 
 int /*<<< orphan*/  buf_out_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cliprdr_send_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
cliprdr_send_data_request(RDPCLIENT * This, uint32 format)
{
	uint8 buffer[4];

	DEBUG_CLIPBOARD(("cliprdr_send_data_request\n"));
	buf_out_uint32(buffer, format);
	cliprdr_send_packet(This, CLIPRDR_DATA_REQUEST, CLIPRDR_REQUEST, buffer, sizeof(buffer));
}