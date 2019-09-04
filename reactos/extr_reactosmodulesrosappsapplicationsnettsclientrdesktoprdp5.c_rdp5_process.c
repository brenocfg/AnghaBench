#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint32 ;
typedef  int uint16 ;
struct stream {int* p; int* end; int* data; int size; int* rdp_hdr; } ;
struct TYPE_14__ {int hist; struct stream ns; } ;
struct TYPE_15__ {int* next_packet; int disconnect_reason; TYPE_1__ mppc_dict; } ;
typedef  struct stream* STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int RDP5_COMPRESSED ; 
 int RDP_MPPC_COMPRESSED ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  in_uint16_le (struct stream*,int) ; 
 int /*<<< orphan*/  in_uint8 (struct stream*,int) ; 
 int /*<<< orphan*/  in_uint8s (struct stream*,int) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,int) ; 
 int mppc_expand (TYPE_2__*,int*,int,int,int*,int*) ; 
 int /*<<< orphan*/  process_bitmap_updates (TYPE_2__*,struct stream*) ; 
 int /*<<< orphan*/  process_cached_pointer_pdu (TYPE_2__*,struct stream*) ; 
 int /*<<< orphan*/  process_colour_pointer_pdu (TYPE_2__*,struct stream*) ; 
 int /*<<< orphan*/  process_orders (TYPE_2__*,struct stream*,int) ; 
 int /*<<< orphan*/  process_palette (TYPE_2__*,struct stream*) ; 
 void* realloc (int*,int) ; 
 int /*<<< orphan*/  s_check (struct stream*) ; 
 int /*<<< orphan*/  ui_begin_update (TYPE_2__*) ; 
 int /*<<< orphan*/  ui_end_update (TYPE_2__*) ; 
 int /*<<< orphan*/  ui_move_pointer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ui_set_null_cursor (TYPE_2__*) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

BOOL
rdp5_process(RDPCLIENT * This, STREAM s)
{
	uint16 length, count, x, y;
	uint8 type, ctype;
	uint8 *next;

	uint32 roff, rlen;
	struct stream *ns = &(This->mppc_dict.ns);
	struct stream *ts;

#if 0
	printf("RDP5 data:\n");
	hexdump(s->p, s->end - s->p);
#endif

	ui_begin_update(This);
	while (s->p < s->end)
	{
		in_uint8(s, type);
		if (type & RDP5_COMPRESSED)
		{
			in_uint8(s, ctype);
			in_uint16_le(s, length);
			type ^= RDP5_COMPRESSED;
		}
		else
		{
			ctype = 0;
			in_uint16_le(s, length);
		}
		This->next_packet = next = s->p + length;

		if (ctype & RDP_MPPC_COMPRESSED)
		{
			void * p;

			if (mppc_expand(This, s->p, length, ctype, &roff, &rlen) == -1)
				error("error while decompressing packet\n");

			/* allocate memory and copy the uncompressed data into the temporary stream */
			p = realloc(ns->data, rlen);

			if(p == NULL)
			{
				This->disconnect_reason = 262;
				return False;
			}

			ns->data = (uint8 *) p;

			memcpy((ns->data), (unsigned char *) (This->mppc_dict.hist + roff), rlen);

			ns->size = rlen;
			ns->end = (ns->data + ns->size);
			ns->p = ns->data;
			ns->rdp_hdr = ns->p;

			ts = ns;
		}
		else
			ts = s;

		switch (type)
		{
			case 0:	/* update orders */
				in_uint16_le(ts, count);
				process_orders(This, ts, count);
				break;
			case 1:	/* update bitmap */
				in_uint8s(ts, 2);	/* part length */
				process_bitmap_updates(This, ts);
				break;
			case 2:	/* update palette */
				in_uint8s(ts, 2);	/* uint16 = 2 */
				process_palette(This, ts);
				break;
			case 3:	/* update synchronize */
				break;
			case 5:	/* null pointer */
				ui_set_null_cursor(This);
				break;
			case 6:	/* default pointer */
				break;
			case 8:	/* pointer position */
				in_uint16_le(ts, x);
				in_uint16_le(ts, y);
				if (s_check(ts))
					ui_move_pointer(This, x, y);
				break;
			case 9:	/* color pointer */
				process_colour_pointer_pdu(This, ts);
				break;
			case 10:	/* cached pointer */
				process_cached_pointer_pdu(This, ts);
				break;
			default:
				unimpl("RDP5 opcode %d\n", type);
		}

		s->p = next;
	}
	ui_end_update(This);
	return True;
}