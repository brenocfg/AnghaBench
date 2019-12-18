#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint16 ;
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__* STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
#define  RDP_CAPSET_BITMAP 129 
#define  RDP_CAPSET_GENERAL 128 
 int /*<<< orphan*/  in_uint16_le (TYPE_1__*,int) ; 
 int /*<<< orphan*/  in_uint8s (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rdp_process_bitmap_caps (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rdp_process_general_caps (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
rdp_process_server_caps(RDPCLIENT * This, STREAM s, uint16 length)
{
	int n;
	uint8 *next, *start;
	uint16 ncapsets, capset_type, capset_length;

	start = s->p;

	in_uint16_le(s, ncapsets);
	in_uint8s(s, 2);	/* pad */

	for (n = 0; n < ncapsets; n++)
	{
		if (s->p > start + length)
			return;

		in_uint16_le(s, capset_type);
		in_uint16_le(s, capset_length);

		next = s->p + capset_length - 4;

		switch (capset_type)
		{
			case RDP_CAPSET_GENERAL:
				rdp_process_general_caps(This, s);
				break;

			case RDP_CAPSET_BITMAP:
				rdp_process_bitmap_caps(This, s);
				break;
		}

		s->p = next;
	}
}