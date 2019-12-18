#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
struct termios {int dummy; } ;
struct TYPE_5__ {int baud_rate; int queue_in_size; int queue_out_size; int control; int xonoff; int onlimit; int offlimit; int read_interval_timeout; int read_total_timeout_multiplier; int read_total_timeout_constant; int write_total_timeout_multiplier; int write_total_timeout_constant; int wait_mask; int dtr; int rts; int event_pending; int /*<<< orphan*/  chars; int /*<<< orphan*/  word_length; int /*<<< orphan*/  parity; int /*<<< orphan*/  stop_bits; struct termios* ptermios; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ SERIAL_DEVICE ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SERIAL (char*) ; 
 int FILE_DEVICE_SERIAL_PORT ; 
#define  SERIAL_CLR_DTR 155 
#define  SERIAL_CLR_RTS 154 
#define  SERIAL_CONFIG_SIZE 153 
#define  SERIAL_GET_BAUD_RATE 152 
#define  SERIAL_GET_CHARS 151 
#define  SERIAL_GET_COMMSTATUS 150 
#define  SERIAL_GET_HANDFLOW 149 
#define  SERIAL_GET_LINE_CONTROL 148 
#define  SERIAL_GET_MODEMSTATUS 147 
#define  SERIAL_GET_TIMEOUTS 146 
#define  SERIAL_GET_WAIT_MASK 145 
#define  SERIAL_IMMEDIATE_CHAR 144 
 int SERIAL_MS_CAR ; 
 int SERIAL_MS_CTS ; 
 int SERIAL_MS_DSR ; 
 int SERIAL_MS_DTR ; 
 int SERIAL_MS_RNG ; 
 int SERIAL_MS_RTS ; 
#define  SERIAL_PURGE 143 
 int SERIAL_PURGE_RXABORT ; 
 int SERIAL_PURGE_RXCLEAR ; 
 int SERIAL_PURGE_TXABORT ; 
 int SERIAL_PURGE_TXCLEAR ; 
#define  SERIAL_RESET_DEVICE 142 
#define  SERIAL_SET_BAUD_RATE 141 
#define  SERIAL_SET_BREAK_OFF 140 
#define  SERIAL_SET_BREAK_ON 139 
#define  SERIAL_SET_CHARS 138 
#define  SERIAL_SET_DTR 137 
#define  SERIAL_SET_HANDFLOW 136 
#define  SERIAL_SET_LINE_CONTROL 135 
#define  SERIAL_SET_QUEUE_SIZE 134 
#define  SERIAL_SET_RTS 133 
#define  SERIAL_SET_TIMEOUTS 132 
#define  SERIAL_SET_WAIT_MASK 131 
#define  SERIAL_SET_XOFF 130 
#define  SERIAL_SET_XON 129 
#define  SERIAL_WAIT_ON_MASK 128 
 int /*<<< orphan*/  STATUS_CANCELLED ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_PENDING ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int TCIFLUSH ; 
 int /*<<< orphan*/  TCION ; 
 int TCOFLUSH ; 
 int /*<<< orphan*/  TIOCINQ ; 
 int /*<<< orphan*/  TIOCMGET ; 
 int /*<<< orphan*/  TIOCMSET ; 
 int TIOCM_CAR ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RNG ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  TIOCOUTQ ; 
 TYPE_1__* get_serial_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_termios (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdpdr_abort_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_get_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_termios (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcflow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcsendbreak (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

__attribute__((used)) static NTSTATUS
serial_device_control(RDPCLIENT * This, NTHANDLE handle, uint32 request, STREAM in, STREAM out)
{
	int flush_mask, purge_mask;
	uint32 result, modemstate;
	uint8 immediate;
	SERIAL_DEVICE *pser_inf;
	struct termios *ptermios;

	if ((request >> 16) != FILE_DEVICE_SERIAL_PORT)
		return STATUS_INVALID_PARAMETER;

	pser_inf = get_serial_info(This, handle);
	ptermios = pser_inf->ptermios;

	/* extract operation */
	request >>= 2;
	request &= 0xfff;

	switch (request)
	{
		case SERIAL_SET_BAUD_RATE:
			in_uint32_le(in, pser_inf->baud_rate);
			set_termios(pser_inf, handle);
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_BAUD_RATE %d\n",
				      pser_inf->baud_rate));
			break;
		case SERIAL_GET_BAUD_RATE:
			out_uint32_le(out, pser_inf->baud_rate);
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_BAUD_RATE %d\n",
				      pser_inf->baud_rate));
			break;
		case SERIAL_SET_QUEUE_SIZE:
			in_uint32_le(in, pser_inf->queue_in_size);
			in_uint32_le(in, pser_inf->queue_out_size);
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_QUEUE_SIZE in %d out %d\n",
				      pser_inf->queue_in_size, pser_inf->queue_out_size));
			break;
		case SERIAL_SET_LINE_CONTROL:
			in_uint8(in, pser_inf->stop_bits);
			in_uint8(in, pser_inf->parity);
			in_uint8(in, pser_inf->word_length);
			set_termios(pser_inf, handle);
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_LINE_CONTROL stop %d parity %d word %d\n", pser_inf->stop_bits, pser_inf->parity, pser_inf->word_length));
			break;
		case SERIAL_GET_LINE_CONTROL:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_LINE_CONTROL\n"));
			out_uint8(out, pser_inf->stop_bits);
			out_uint8(out, pser_inf->parity);
			out_uint8(out, pser_inf->word_length);
			break;
		case SERIAL_IMMEDIATE_CHAR:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_IMMEDIATE_CHAR\n"));
			in_uint8(in, immediate);
			serial_write(This, handle, &immediate, 1, 0, &result);
			break;
		case SERIAL_CONFIG_SIZE:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_CONFIG_SIZE\n"));
			out_uint32_le(out, 0);
			break;
		case SERIAL_GET_CHARS:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_CHARS\n"));
			out_uint8a(out, pser_inf->chars, 6);
			break;
		case SERIAL_SET_CHARS:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_CHARS\n"));
			in_uint8a(in, pser_inf->chars, 6);
#ifdef WITH_DEBUG_SERIAL
			hexdump(pser_inf->chars, 6);
#endif
			set_termios(pser_inf, handle);
			break;
		case SERIAL_GET_HANDFLOW:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_HANDFLOW\n"));
			get_termios(pser_inf, handle);
			out_uint32_le(out, pser_inf->control);
			out_uint32_le(out, pser_inf->xonoff);	/* Xon/Xoff */
			out_uint32_le(out, pser_inf->onlimit);
			out_uint32_le(out, pser_inf->offlimit);
			break;
		case SERIAL_SET_HANDFLOW:
			in_uint32_le(in, pser_inf->control);
			in_uint32_le(in, pser_inf->xonoff);
			in_uint32_le(in, pser_inf->onlimit);
			in_uint32_le(in, pser_inf->offlimit);
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_HANDFLOW %x %x %x %x\n",
				      pser_inf->control, pser_inf->xonoff, pser_inf->onlimit,
				      pser_inf->onlimit));
			set_termios(pser_inf, handle);
			break;
		case SERIAL_SET_TIMEOUTS:
			in_uint32(in, pser_inf->read_interval_timeout);
			in_uint32(in, pser_inf->read_total_timeout_multiplier);
			in_uint32(in, pser_inf->read_total_timeout_constant);
			in_uint32(in, pser_inf->write_total_timeout_multiplier);
			in_uint32(in, pser_inf->write_total_timeout_constant);
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_TIMEOUTS read timeout %d %d %d\n",
				      pser_inf->read_interval_timeout,
				      pser_inf->read_total_timeout_multiplier,
				      pser_inf->read_total_timeout_constant));
			break;
		case SERIAL_GET_TIMEOUTS:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_TIMEOUTS read timeout %d %d %d\n",
				      pser_inf->read_interval_timeout,
				      pser_inf->read_total_timeout_multiplier,
				      pser_inf->read_total_timeout_constant));

			out_uint32(out, pser_inf->read_interval_timeout);
			out_uint32(out, pser_inf->read_total_timeout_multiplier);
			out_uint32(out, pser_inf->read_total_timeout_constant);
			out_uint32(out, pser_inf->write_total_timeout_multiplier);
			out_uint32(out, pser_inf->write_total_timeout_constant);
			break;
		case SERIAL_GET_WAIT_MASK:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_WAIT_MASK %X\n",
				      pser_inf->wait_mask));
			out_uint32(out, pser_inf->wait_mask);
			break;
		case SERIAL_SET_WAIT_MASK:
			in_uint32(in, pser_inf->wait_mask);
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_WAIT_MASK %X\n",
				      pser_inf->wait_mask));
			break;
		case SERIAL_SET_DTR:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_DTR\n"));
			ioctl(handle, TIOCMGET, &result);
			result |= TIOCM_DTR;
			ioctl(handle, TIOCMSET, &result);
			pser_inf->dtr = 1;
			break;
		case SERIAL_CLR_DTR:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_CLR_DTR\n"));
			ioctl(handle, TIOCMGET, &result);
			result &= ~TIOCM_DTR;
			ioctl(handle, TIOCMSET, &result);
			pser_inf->dtr = 0;
			break;
		case SERIAL_SET_RTS:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_RTS\n"));
			ioctl(handle, TIOCMGET, &result);
			result |= TIOCM_RTS;
			ioctl(handle, TIOCMSET, &result);
			pser_inf->rts = 1;
			break;
		case SERIAL_CLR_RTS:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_CLR_RTS\n"));
			ioctl(handle, TIOCMGET, &result);
			result &= ~TIOCM_RTS;
			ioctl(handle, TIOCMSET, &result);
			pser_inf->rts = 0;
			break;
		case SERIAL_GET_MODEMSTATUS:
			modemstate = 0;
#ifdef TIOCMGET
			ioctl(handle, TIOCMGET, &result);
			if (result & TIOCM_CTS)
				modemstate |= SERIAL_MS_CTS;
			if (result & TIOCM_DSR)
				modemstate |= SERIAL_MS_DSR;
			if (result & TIOCM_RNG)
				modemstate |= SERIAL_MS_RNG;
			if (result & TIOCM_CAR)
				modemstate |= SERIAL_MS_CAR;
			if (result & TIOCM_DTR)
				modemstate |= SERIAL_MS_DTR;
			if (result & TIOCM_RTS)
				modemstate |= SERIAL_MS_RTS;
#endif
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_MODEMSTATUS %X\n", modemstate));
			out_uint32_le(out, modemstate);
			break;
		case SERIAL_GET_COMMSTATUS:
			out_uint32_le(out, 0);	/* Errors */
			out_uint32_le(out, 0);	/* Hold reasons */

			result = 0;
#ifdef TIOCINQ
			ioctl(handle, TIOCINQ, &result);
#endif
			out_uint32_le(out, result);	/* Amount in in queue */
			if (result)
				DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_COMMSTATUS in queue %d\n",
					      result));

			result = 0;
#ifdef TIOCOUTQ
			ioctl(handle, TIOCOUTQ, &result);
#endif
			out_uint32_le(out, result);	/* Amount in out queue */
			if (result)
				DEBUG_SERIAL(("serial_ioctl -> SERIAL_GET_COMMSTATUS out queue %d\n", result));

			out_uint8(out, 0);	/* EofReceived */
			out_uint8(out, 0);	/* WaitForImmediate */
			break;
		case SERIAL_PURGE:
			in_uint32(in, purge_mask);
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_PURGE purge_mask %X\n", purge_mask));
			flush_mask = 0;
			if (purge_mask & SERIAL_PURGE_TXCLEAR)
				flush_mask |= TCOFLUSH;
			if (purge_mask & SERIAL_PURGE_RXCLEAR)
				flush_mask |= TCIFLUSH;
			if (flush_mask != 0)
				tcflush(handle, flush_mask);
			if (purge_mask & SERIAL_PURGE_TXABORT)
				rdpdr_abort_io(This, handle, 4, STATUS_CANCELLED);
			if (purge_mask & SERIAL_PURGE_RXABORT)
				rdpdr_abort_io(This, handle, 3, STATUS_CANCELLED);
			break;
		case SERIAL_WAIT_ON_MASK:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_WAIT_ON_MASK %X\n",
				      pser_inf->wait_mask));
			pser_inf->event_pending = 1;
			if (serial_get_event(This, handle, &result))
			{
				DEBUG_SERIAL(("WAIT end  event = %x\n", result));
				out_uint32_le(out, result);
				break;
			}
			return STATUS_PENDING;
			break;
		case SERIAL_SET_BREAK_ON:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_BREAK_ON\n"));
			tcsendbreak(handle, 0);
			break;
		case SERIAL_RESET_DEVICE:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_RESET_DEVICE\n"));
			break;
		case SERIAL_SET_BREAK_OFF:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_BREAK_OFF\n"));
			break;
		case SERIAL_SET_XOFF:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_XOFF\n"));
			break;
		case SERIAL_SET_XON:
			DEBUG_SERIAL(("serial_ioctl -> SERIAL_SET_XON\n"));
			tcflow(handle, TCION);
			break;
		default:
			unimpl("SERIAL IOCTL %d\n", request);
			return STATUS_INVALID_PARAMETER;
	}

	return STATUS_SUCCESS;
}