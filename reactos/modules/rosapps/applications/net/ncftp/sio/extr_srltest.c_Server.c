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
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 int SAccept (int,struct sockaddr_in*,int) ; 
 int SNewStreamServer (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ServeOneClient (int,struct sockaddr_in*) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kReUseAddrYes ; 
 int kTimeoutErr ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Server(int port)
{
	int sockfd, newsockfd;
	struct sockaddr_in cliAddr;
	int pid;

	sockfd = SNewStreamServer(port, 3, kReUseAddrYes, 3);
	if (sockfd < 0) {
		perror("Server setup failed");
		exit(1);
	}

	printf("server[%d]: started.\n", (int) getpid());
	for(;;) {
		while (waitpid(-1, NULL, WNOHANG) > 0) ;
		newsockfd = SAccept(sockfd, &cliAddr, 5);
		if (newsockfd < 0) {
			if (newsockfd == kTimeoutErr)
				printf("server[%d]: idle\n", (int) getpid());
			else
				fprintf(stderr, "server[%d]: accept error: %s\n",
					(int) getpid(), strerror(errno));
		} else if ((pid = fork()) < 0) {
			fprintf(stderr, "server[%d]: fork error: %s\n",
				(int) getpid(), strerror(errno));
			exit(1);
		} else if (pid == 0) {
			ServeOneClient(newsockfd, &cliAddr);
			exit(0);
		} else {
			/* Parent doesn't need it now. */
			(void) close(newsockfd);
		}
	}
}