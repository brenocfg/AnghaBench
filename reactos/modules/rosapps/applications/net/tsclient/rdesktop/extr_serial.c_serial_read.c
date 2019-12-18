#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
struct termios {long* c_cc; } ;
struct TYPE_3__ {int read_total_timeout_multiplier; int read_total_timeout_constant; int read_interval_timeout; struct termios* ptermios; } ;
typedef  TYPE_1__ SERIAL_DEVICE ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SERIAL (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCINQ ; 
 size_t VMIN ; 
 size_t VTIME ; 
 TYPE_1__* get_serial_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static NTSTATUS
serial_read(RDPCLIENT * This, NTHANDLE handle, uint8 * data, uint32 length, uint32 offset, uint32 * result)
{
	long timeout;
	SERIAL_DEVICE *pser_inf;
	struct termios *ptermios;
#ifdef WITH_DEBUG_SERIAL
	int bytes_inqueue;
#endif


	timeout = 90;
	pser_inf = get_serial_info(This, handle);
	ptermios = pser_inf->ptermios;

	/* Set timeouts kind of like the windows serial timeout parameters. Multiply timeout
	   with requested read size */
	if (pser_inf->read_total_timeout_multiplier | pser_inf->read_total_timeout_constant)
	{
		timeout =
			(pser_inf->read_total_timeout_multiplier * length +
			 pser_inf->read_total_timeout_constant + 99) / 100;
	}
	else if (pser_inf->read_interval_timeout)
	{
		timeout = (pser_inf->read_interval_timeout * length + 99) / 100;
	}

	/* If a timeout is set, do a blocking read, which times out after some time.
	   It will make rdesktop less responsive, but it will improve serial performance, by not
	   reading one character at a time. */
	if (timeout == 0)
	{
		ptermios->c_cc[VTIME] = 0;
		ptermios->c_cc[VMIN] = 0;
	}
	else
	{
		ptermios->c_cc[VTIME] = timeout;
		ptermios->c_cc[VMIN] = 1;
	}
	tcsetattr(handle, TCSANOW, ptermios);

#if defined(WITH_DEBUG_SERIAL) && defined(TIOCINQ)
	ioctl(handle, TIOCINQ, &bytes_inqueue);
	DEBUG_SERIAL(("serial_read inqueue: %d expected %d\n", bytes_inqueue, length));
#endif

	*result = read(handle, data, length);

#ifdef WITH_DEBUG_SERIAL
	DEBUG_SERIAL(("serial_read Bytes %d\n", *result));
	if (*result > 0)
		hexdump(data, *result);
#endif

	return STATUS_SUCCESS;
}