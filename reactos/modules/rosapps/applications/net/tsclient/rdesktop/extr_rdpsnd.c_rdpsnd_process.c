#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint32 ;
typedef  size_t uint16 ;
struct TYPE_16__ {size_t current_format; void* device_open; int /*<<< orphan*/ * formats; } ;
struct TYPE_18__ {TYPE_1__ rdpsnd; } ;
struct TYPE_17__ {scalar_t__ p; scalar_t__ end; } ;
typedef  TYPE_2__* STREAM ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  void* BOOL ;

/* Variables and functions */
 void* False ; 
 size_t MAX_FORMATS ; 
#define  RDPSND_CLOSE 132 
#define  RDPSND_NEGOTIATE 131 
#define  RDPSND_SERVERTICK 130 
#define  RDPSND_SET_VOLUME 129 
#define  RDPSND_WRITE 128 
 void* True ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  hexdump (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  in_uint16_le (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  in_uint32 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  in_uint8 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  in_uint8s (TYPE_2__*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rdpsnd_process_negotiate (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  rdpsnd_process_servertick (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  rdpsnd_send_completion (TYPE_3__*,size_t,int) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 
 int /*<<< orphan*/  wave_out_close () ; 
 int /*<<< orphan*/  wave_out_open () ; 
 int /*<<< orphan*/  wave_out_set_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wave_out_volume (int,int) ; 
 int /*<<< orphan*/  wave_out_write (TYPE_2__*,size_t,int) ; 

__attribute__((used)) static void
rdpsnd_process(RDPCLIENT * This, STREAM s)
{
	uint8 type;
	uint16 datalen;
	uint32 volume;
	static uint16 tick, format;
	static uint8 packet_index;
	static BOOL awaiting_data_packet;

#ifdef RDPSND_DEBUG
	printf("RDPSND recv:\n");
	hexdump(s->p, s->end - s->p);
#endif

	if (awaiting_data_packet)
	{
		if (format >= MAX_FORMATS)
		{
			error("RDPSND: Invalid format index\n");
			return;
		}

		if (!This->rdpsnd.device_open || (format != This->rdpsnd.current_format))
		{
			if (!This->rdpsnd.device_open && !wave_out_open())
			{
				rdpsnd_send_completion(This, tick, packet_index);
				return;
			}
			if (!wave_out_set_format(&This->rdpsnd.formats[format]))
			{
				rdpsnd_send_completion(This, tick, packet_index);
				wave_out_close();
				This->rdpsnd.device_open = False;
				return;
			}
			This->rdpsnd.device_open = True;
			This->rdpsnd.current_format = format;
		}

		wave_out_write(s, tick, packet_index);
		awaiting_data_packet = False;
		return;
	}

	in_uint8(s, type);
	in_uint8s(s, 1);	/* unknown? */
	in_uint16_le(s, datalen);

	switch (type)
	{
		case RDPSND_WRITE:
			in_uint16_le(s, tick);
			in_uint16_le(s, format);
			in_uint8(s, packet_index);
			awaiting_data_packet = True;
			break;
		case RDPSND_CLOSE:
			wave_out_close();
			This->rdpsnd.device_open = False;
			break;
		case RDPSND_NEGOTIATE:
			rdpsnd_process_negotiate(This, s);
			break;
		case RDPSND_SERVERTICK:
			rdpsnd_process_servertick(This, s);
			break;
		case RDPSND_SET_VOLUME:
			in_uint32(s, volume);
			if (This->rdpsnd.device_open)
			{
				wave_out_volume((volume & 0xffff), (volume & 0xffff0000) >> 16);
			}
			break;
		default:
			unimpl("RDPSND packet type %d\n", type);
			break;
	}
}