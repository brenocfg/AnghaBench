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
struct sockaddr_un {char* sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

int
main(int argc, char *argv[])
{
	struct sockaddr_un sock;
	int fd;
	char *path;
	size_t size;
	if (argc != 2) {
		fprintf(stderr, "usage: %s /path/to/socket\n", argv[0]);
		exit(1);
	}
	path = argv[1];
	size =  sizeof (sock.sun_path);
	strncpy(sock.sun_path, (char *)path, size - 1);
	sock.sun_path[size - 1] = '\0';

	sock.sun_family = AF_UNIX;
	if ((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return (1);
	}
	if (bind(fd, (struct sockaddr *)&sock, sizeof (struct sockaddr_un))) {
		perror("bind");
		return (1);
	}
	if (close(fd)) {
		perror("close");
		return (1);
	}
	return (0);
}