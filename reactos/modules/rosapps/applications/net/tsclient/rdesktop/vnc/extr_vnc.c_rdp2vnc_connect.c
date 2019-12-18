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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint32 ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rdp_connect (char*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  rdp_disconnect () ; 
 int /*<<< orphan*/  rdp_main_loop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rfbClientSocket ; 
 int rfbListenOnTCPPort (int) ; 
 int rfb_port ; 
 scalar_t__ select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_create_window () ; 
 int /*<<< orphan*/  ui_destroy_window () ; 

void
rdp2vnc_connect(char *server, uint32 flags, char *domain, char *password,
		char *shell, char *directory)
{
	struct sockaddr addr;
	fd_set fdset;
	struct timeval tv;
	int rfbListenSock, addrlen = sizeof(addr);

	rfbListenSock = rfbListenOnTCPPort(rfb_port);
	fprintf(stderr, "Listening on VNC port %d\n", rfb_port);
	if (rfbListenSock <= 0)
		error("Cannot listen on port %d", rfb_port);
	else
		while (1)
		{
			FD_ZERO(&fdset);
			FD_SET(rfbListenSock, &fdset);
			tv.tv_sec = 5;
			tv.tv_usec = 0;
			if (select(rfbListenSock + 1, &fdset, NULL, NULL, &tv) > 0)
			{
				rfbClientSocket = accept(rfbListenSock, &addr, &addrlen);
				if (rfbClientSocket < 0)
				{
					error("Error accepting client (%d: %s.\n",
					      errno, strerror(errno));
					continue;
				}
				ui_create_window();
				if (!rdp_connect(server, flags, domain, password, shell, directory))
				{
					error("Error connecting to RDP server.\n");
					continue;
				}
				if (!fork())
				{
					BOOL deactivated;
					uint32_t ext_disc_reason;
					printf("Connection successful.\n");
					rdp_main_loop(&deactivated, &ext_disc_reason);
					printf("Disconnecting...\n");
					rdp_disconnect();
					ui_destroy_window();
					exit(0);
				}
			}
		}
}