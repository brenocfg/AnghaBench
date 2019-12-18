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
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLIPRDR_DATA_RESPONSE ; 
 int /*<<< orphan*/  CLIPRDR_RESPONSE ; 
 int /*<<< orphan*/  DEBUG_CLIPBOARD (char*) ; 
 int /*<<< orphan*/  cliprdr_send_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
cliprdr_send_data(RDPCLIENT * This, uint8 * data, uint32 length)
{
	DEBUG_CLIPBOARD(("cliprdr_send_data\n"));
	cliprdr_send_packet(This, CLIPRDR_DATA_RESPONSE, CLIPRDR_RESPONSE, data, length);
}