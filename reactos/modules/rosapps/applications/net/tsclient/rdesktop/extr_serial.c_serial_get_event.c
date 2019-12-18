#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {TYPE_1__* rdpdr_device; } ;
struct TYPE_7__ {int event_rlsd; int wait_mask; int event_txempty; int event_dsr; int event_cts; scalar_t__ event_pending; } ;
struct TYPE_6__ {scalar_t__ pdevice_data; } ;
typedef  TYPE_2__ SERIAL_DEVICE ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  int /*<<< orphan*/  NTHANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SERIAL (char*) ; 
 scalar_t__ False ; 
 int SERIAL_EV_CTS ; 
 int SERIAL_EV_DSR ; 
 int SERIAL_EV_RLSD ; 
 int SERIAL_EV_RXCHAR ; 
 int SERIAL_EV_RXFLAG ; 
 int SERIAL_EV_TXEMPTY ; 
 int /*<<< orphan*/  TIOCINQ ; 
 int /*<<< orphan*/  TIOCMGET ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int /*<<< orphan*/  TIOCOUTQ ; 
 scalar_t__ True ; 
 int get_device_index (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

BOOL
serial_get_event(RDPCLIENT * This, NTHANDLE handle, uint32 * result)
{
	int index;
	SERIAL_DEVICE *pser_inf;
	int bytes;
	BOOL ret = False;

	*result = 0;
	index = get_device_index(This, handle);
	if (index < 0)
		return False;

#ifdef TIOCINQ
	pser_inf = (SERIAL_DEVICE *) This->rdpdr_device[index].pdevice_data;

	ioctl(handle, TIOCINQ, &bytes);

	if (bytes > 0)
	{
		DEBUG_SERIAL(("serial_get_event Bytes %d\n", bytes));
		if (bytes > pser_inf->event_rlsd)
		{
			pser_inf->event_rlsd = bytes;
			if (pser_inf->wait_mask & SERIAL_EV_RLSD)
			{
				DEBUG_SERIAL(("Event -> SERIAL_EV_RLSD \n"));
				*result |= SERIAL_EV_RLSD;
				ret = True;
			}

		}

		if ((bytes > 1) && (pser_inf->wait_mask & SERIAL_EV_RXFLAG))
		{
			DEBUG_SERIAL(("Event -> SERIAL_EV_RXFLAG Bytes %d\n", bytes));
			*result |= SERIAL_EV_RXFLAG;
			ret = True;
		}
		if ((pser_inf->wait_mask & SERIAL_EV_RXCHAR))
		{
			DEBUG_SERIAL(("Event -> SERIAL_EV_RXCHAR Bytes %d\n", bytes));
			*result |= SERIAL_EV_RXCHAR;
			ret = True;
		}

	}
	else
	{
		pser_inf->event_rlsd = 0;
	}
#endif

#ifdef TIOCOUTQ
	ioctl(handle, TIOCOUTQ, &bytes);
	if ((bytes == 0)
	    && (pser_inf->event_txempty > 0) && (pser_inf->wait_mask & SERIAL_EV_TXEMPTY))
	{

		DEBUG_SERIAL(("Event -> SERIAL_EV_TXEMPTY\n"));
		*result |= SERIAL_EV_TXEMPTY;
		ret = True;
	}
	pser_inf->event_txempty = bytes;
#endif

	ioctl(handle, TIOCMGET, &bytes);
	if ((bytes & TIOCM_DSR) != pser_inf->event_dsr)
	{
		pser_inf->event_dsr = bytes & TIOCM_DSR;
		if (pser_inf->wait_mask & SERIAL_EV_DSR)
		{
			DEBUG_SERIAL(("event -> SERIAL_EV_DSR %s\n",
				      (bytes & TIOCM_DSR) ? "ON" : "OFF"));
			*result |= SERIAL_EV_DSR;
			ret = True;
		}
	}

	if ((bytes & TIOCM_CTS) != pser_inf->event_cts)
	{
		pser_inf->event_cts = bytes & TIOCM_CTS;
		if (pser_inf->wait_mask & SERIAL_EV_CTS)
		{
			DEBUG_SERIAL((" EVENT-> SERIAL_EV_CTS %s\n",
				      (bytes & TIOCM_CTS) ? "ON" : "OFF"));
			*result |= SERIAL_EV_CTS;
			ret = True;
		}
	}

	if (ret)
		pser_inf->event_pending = 0;

	return ret;
}