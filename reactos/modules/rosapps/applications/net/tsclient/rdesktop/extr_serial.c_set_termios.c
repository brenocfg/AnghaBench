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
struct termios {int c_cflag; int c_iflag; int /*<<< orphan*/ * c_cc; } ;
typedef  int speed_t ;
struct TYPE_3__ {int baud_rate; int stop_bits; int parity; int word_length; int control; int xonoff; int /*<<< orphan*/ * chars; scalar_t__ rts; scalar_t__ dtr; struct termios* ptermios; } ;
typedef  TYPE_1__ SERIAL_DEVICE ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
 int B110 ; 
 int B115200 ; 
 int B1200 ; 
 int B134 ; 
 int B150 ; 
 int B1800 ; 
 int B19200 ; 
 int B2400 ; 
 int B300 ; 
 int B38400 ; 
 int B4800 ; 
 int B57600 ; 
 int B600 ; 
 int B75 ; 
 int B9600 ; 
 int CBAUD ; 
 int CRTSCTS ; 
 int CS5 ; 
 int CS6 ; 
 int CS7 ; 
 int CS8 ; 
 int CSIZE ; 
 int CSTOPB ; 
#define  EVEN_PARITY 131 
 int IMAXBEL ; 
 int IXOFF ; 
 int IXON ; 
#define  NO_PARITY 130 
#define  ODD_PARITY 129 
 int PARENB ; 
 int PARODD ; 
 size_t SERIAL_CHAR_BREAK ; 
 size_t SERIAL_CHAR_EOF ; 
 size_t SERIAL_CHAR_ERROR ; 
 size_t SERIAL_CHAR_XOFF ; 
 size_t SERIAL_CHAR_XON ; 
 int SERIAL_CTS_HANDSHAKE ; 
 int SERIAL_XOFF_HANDSHAKE ; 
 int SERIAL_XON_HANDSHAKE ; 
#define  STOP_BITS_2 128 
 int /*<<< orphan*/  TCSANOW ; 
 size_t VEOF ; 
 size_t VINTR ; 
 size_t VKILL ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void
set_termios(SERIAL_DEVICE * pser_inf, NTHANDLE serial_fd)
{
	speed_t speed;

	struct termios *ptermios;

	ptermios = pser_inf->ptermios;


	switch (pser_inf->baud_rate)
	{
#ifdef B75
		case 75:
			speed = B75;
			break;
#endif
#ifdef B110
		case 110:
			speed = B110;
			break;
#endif
#ifdef B134
		case 134:
			speed = B134;
			break;
#endif
#ifdef B150
		case 150:
			speed = B150;
			break;
#endif
#ifdef B300
		case 300:
			speed = B300;
			break;
#endif
#ifdef B600
		case 600:
			speed = B600;
			break;
#endif
#ifdef B1200
		case 1200:
			speed = B1200;
			break;
#endif
#ifdef B1800
		case 1800:
			speed = B1800;
			break;
#endif
#ifdef B2400
		case 2400:
			speed = B2400;
			break;
#endif
#ifdef B4800
		case 4800:
			speed = B4800;
			break;
#endif
#ifdef B9600
		case 9600:
			speed = B9600;
			break;
#endif
#ifdef B19200
		case 19200:
			speed = B19200;
			break;
#endif
#ifdef B38400
		case 38400:
			speed = B38400;
			break;
#endif
#ifdef B57600
		case 57600:
			speed = B57600;
			break;
#endif
#ifdef B115200
		case 115200:
			speed = B115200;
			break;
#endif
#ifdef B230400
		case 230400:
			speed = B115200;
			break;
#endif
#ifdef B460800
		case 460800:
			speed = B115200;
			break;
#endif
		default:
			speed = B9600;
			break;
	}

#ifdef CBAUD
	ptermios->c_cflag &= ~CBAUD;
	ptermios->c_cflag |= speed;
#else
	/* on systems with separate ispeed and ospeed, we can remember the speed
	   in ispeed while changing DTR with ospeed */
	cfsetispeed(pser_inf->ptermios, speed);
	cfsetospeed(pser_inf->ptermios, pser_inf->dtr ? speed : 0);
#endif

	ptermios->c_cflag &= ~(CSTOPB | PARENB | PARODD | CSIZE | CRTSCTS);
	switch (pser_inf->stop_bits)
	{
		case STOP_BITS_2:
			ptermios->c_cflag |= CSTOPB;
			break;
		default:
			ptermios->c_cflag &= ~CSTOPB;
			break;
	}

	switch (pser_inf->parity)
	{
		case EVEN_PARITY:
			ptermios->c_cflag |= PARENB;
			break;
		case ODD_PARITY:
			ptermios->c_cflag |= PARENB | PARODD;
			break;
		case NO_PARITY:
			ptermios->c_cflag &= ~(PARENB | PARODD);
			break;
	}

	switch (pser_inf->word_length)
	{
		case 5:
			ptermios->c_cflag |= CS5;
			break;
		case 6:
			ptermios->c_cflag |= CS6;
			break;
		case 7:
			ptermios->c_cflag |= CS7;
			break;
		default:
			ptermios->c_cflag |= CS8;
			break;
	}

#if 0
	if (pser_inf->rts)
		ptermios->c_cflag |= CRTSCTS;
	else
		ptermios->c_cflag &= ~CRTSCTS;
#endif

	if (pser_inf->control & SERIAL_CTS_HANDSHAKE)
	{
		ptermios->c_cflag |= CRTSCTS;
	}
	else
	{
		ptermios->c_cflag &= ~CRTSCTS;
	}


	if (pser_inf->xonoff & SERIAL_XON_HANDSHAKE)
	{
		ptermios->c_iflag |= IXON | IMAXBEL;
	}
	if (pser_inf->xonoff & SERIAL_XOFF_HANDSHAKE)
	{
		ptermios->c_iflag |= IXOFF | IMAXBEL;
	}

	if ((pser_inf->xonoff & (SERIAL_XOFF_HANDSHAKE | SERIAL_XON_HANDSHAKE)) == 0)
	{
		ptermios->c_iflag &= ~IXON;
		ptermios->c_iflag &= ~IXOFF;
	}

	ptermios->c_cc[VSTART] = pser_inf->chars[SERIAL_CHAR_XON];
	ptermios->c_cc[VSTOP] = pser_inf->chars[SERIAL_CHAR_XOFF];
	ptermios->c_cc[VEOF] = pser_inf->chars[SERIAL_CHAR_EOF];
	ptermios->c_cc[VINTR] = pser_inf->chars[SERIAL_CHAR_BREAK];
	ptermios->c_cc[VKILL] = pser_inf->chars[SERIAL_CHAR_ERROR];

	tcsetattr(serial_fd, TCSANOW, ptermios);
}