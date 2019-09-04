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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  HCURSOR ;

/* Variables and functions */
 int /*<<< orphan*/  cache_put_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_create_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_set_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
process_colour_pointer_pdu(RDPCLIENT * This, STREAM s)
{
	uint16 x, y, width, height, cache_idx, masklen, datalen;
	uint8 *mask, *data;
	HCURSOR cursor;

	in_uint16_le(s, cache_idx);
	in_uint16_le(s, x);
	in_uint16_le(s, y);
	in_uint16_le(s, width);
	in_uint16_le(s, height);
	in_uint16_le(s, masklen);
	in_uint16_le(s, datalen);
	in_uint8p(s, data, datalen);
	in_uint8p(s, mask, masklen);
	cursor = ui_create_cursor(This, x, y, width, height, mask, data);
	ui_set_cursor(This, cursor);
	cache_put_cursor(This, cache_idx, cursor);
}