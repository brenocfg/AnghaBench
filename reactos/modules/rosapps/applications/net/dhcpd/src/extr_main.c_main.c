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
struct sockaddr_in {int /*<<< orphan*/  sin_zero; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  DHCPOPTIONS ;
typedef  int /*<<< orphan*/  DHCPMESSAGE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  MYPORT ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ display_dhcp_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_leases_list () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ parse_dhcp_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ process_dhcp_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int recvfrom (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main( int argc, char *argv[] )
{
#ifdef __MINGW32__
  WSADATA wsaData;
  int nCode;
#endif
  int sockfd;
  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  int addr_len, numbytes;
  DHCPMESSAGE dhcpm;
  DHCPOPTIONS dhcpo;

#ifdef __MINGW32__
  if ((nCode = WSAStartup(MAKEWORD(1, 1), &wsaData)) != 0)
    {
      perror("WSAStartup");
      return 0;
    }
#endif

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    perror("socket");
    exit(1);
  }

  init_leases_list();

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  memset(&(my_addr.sin_zero), '\0', 8);

  if (bind(sockfd, (struct sockaddr *)&my_addr,
	   sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  addr_len = sizeof(struct sockaddr);
  while((numbytes=recvfrom(sockfd,&dhcpm, sizeof( DHCPMESSAGE ), 0,
			 (struct sockaddr *)&their_addr, &addr_len)) != -1) {
    /* Parse DHCP */
    display_dhcp_packet( &dhcpm, &dhcpo );
    if( parse_dhcp_options( &dhcpm, &dhcpo ) < 0 )
      continue;
    if( display_dhcp_packet( &dhcpm, &dhcpo ) < 0 )
      continue;
    if( process_dhcp_packet( &dhcpm, &dhcpo ) < 0 )
      continue;
  }

  close(sockfd);

#ifdef __MINGW32__
  WSACleanup();
#endif

  return 0;

}