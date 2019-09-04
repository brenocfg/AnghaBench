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
struct in_addr {int s_addr; } ;
struct sockaddr_in {struct in_addr sin_addr; int /*<<< orphan*/  sin_zero; void* sin_port; void* sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {scalar_t__ h_addr; } ;
typedef  int /*<<< orphan*/  enable ;
typedef  int /*<<< orphan*/  DHCPMESSAGE ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 void* htons (int) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int sendto (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 

int write_packet( DHCPMESSAGE *dhcpm, char *name )
{
  int sockfd;
  struct sockaddr_in their_addr; // connector's address information
  struct hostent *he;
  int numbytes;
  int enable = 1;

  fprintf( stdout, "write_packet [begin]\n" );

  if( !dhcpm )
    return -1;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  if( setsockopt( sockfd, SOL_SOCKET, SO_BROADCAST, &enable, sizeof( enable )) == -1 )
    {
      perror("setsockopt");
      exit(1);
    }

  if( strcmp( "255.255.255.255", name ) )
    {
      if ((he=gethostbyname(name)) == NULL) {  // get the host info
	perror("gethostbyname");
	fprintf( stdout, "Unknown host %s \n", name );
	return -1;
      }
      their_addr.sin_family = AF_INET;     // host byte order
      their_addr.sin_port = htons(68); // short, network byte order
      their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    } else {
      their_addr.sin_family = AF_INET;     // host byte order
      their_addr.sin_port = htons(68); // short, network byte order
      their_addr.sin_addr.s_addr = 0xFFFFFFFF;
    }

  fprintf( stdout, "IP a buscar: %s \n", name );
  memset(&(their_addr.sin_zero), '\0', 8); // zero the rest of the struct

  if ((numbytes=sendto(sockfd, dhcpm, sizeof(DHCPMESSAGE), 0,
		       (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
    perror("sendto");
    exit(1);
  }

  printf("sent %d bytes to %s\n", numbytes,
	 inet_ntoa(their_addr.sin_addr));

  close(sockfd);

  fprintf( stdout, "write_packet [end]\n" );

  return 0;
}