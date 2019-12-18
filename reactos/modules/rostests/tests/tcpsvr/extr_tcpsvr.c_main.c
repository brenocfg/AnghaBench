#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  servAddr ;
typedef  int /*<<< orphan*/  cliAddr ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ERROR ; 
 int FALSE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int MAX_MSG ; 
 int SERVER_PORT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WSACleanup () ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 char* inet_ntoa (TYPE_1__) ; 
 int /*<<< orphan*/  listen (int,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_line (int,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (int argc, char *argv[]) {

  WORD       wVersionRequested;
  WSADATA    WsaData;
  INT	     Status;
  int sd, newSd, cliLen;

  struct sockaddr_in cliAddr, servAddr;
  char line[MAX_MSG];

    wVersionRequested = MAKEWORD(2, 2);

    Status = WSAStartup(wVersionRequested, &WsaData);
    if (Status != 0) {
        printf("Could not initialize winsock dll.\n");
        return FALSE;
    }

  /* create socket */
  sd = socket(AF_INET, SOCK_STREAM, 0);
   if(sd<0) {
    perror("cannot open socket ");
    WSACleanup();
    return ERROR;
  }

  /* bind server port */
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(SERVER_PORT);

  if(bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr))<0) {
    perror("cannot bind port ");
    WSACleanup();
    return ERROR;
  }

  listen(sd,5);

  while(1) {

    printf("%s: \n"
          "To start test, Please telnet to localhost (127.0.0.1) port 23 \n"
          "When connected input raw data followed by End of Line\n"
          "Test is now running on TCP port %u\n",argv[0],SERVER_PORT);

    cliLen = sizeof(cliAddr);
    newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
    if(newSd<0) {
      perror("cannot accept connection ");
      WSACleanup();
      return ERROR;
    }

    /* init line */
    memset(line,0x0,MAX_MSG);

    /* receive segments */
    while(read_line(newSd,line)!=ERROR) {

      printf("%s: received from %s:TCP%d : %s\n", argv[0],
	     inet_ntoa(cliAddr.sin_addr),
	     ntohs(cliAddr.sin_port), line);
      /* init line */
      memset(line,0x0,MAX_MSG);

    } /* while(read_line) */

  } /* while (1) */

}