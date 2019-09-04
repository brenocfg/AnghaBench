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
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  RDP_DATA_PDU_FONT2 ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rdp_init_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rdp_send_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
rdp_send_fonts(RDPCLIENT * This, uint16 seq)
{
	STREAM s;

	s = rdp_init_data(This, 8);

	if(s == NULL)
		return False;

	out_uint16(s, 0);	/* number of fonts */
	out_uint16_le(s, 0);	/* pad? */
	out_uint16_le(s, seq);	/* unknown */
	out_uint16_le(s, 0x32);	/* entry size */

	s_mark_end(s);
	return rdp_send_data(This, s, RDP_DATA_PDU_FONT2);
}