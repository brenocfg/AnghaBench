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
struct sigaction {int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;
struct TYPE_2__ {size_t len; int type; } ;
struct imsg {char* data; TYPE_1__ hdr; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_EXIT_DETACHED ; 
 int /*<<< orphan*/  CLIENT_EXIT_DETACHED_HUP ; 
 int /*<<< orphan*/  CLIENT_EXIT_EXITED ; 
 int /*<<< orphan*/  CLIENT_EXIT_SERVER_EXITED ; 
 size_t IMSG_HEADER_SIZE ; 
#define  MSG_DETACH 135 
#define  MSG_DETACHKILL 134 
#define  MSG_EXEC 133 
#define  MSG_EXIT 132 
#define  MSG_EXITED 131 
 int /*<<< orphan*/  MSG_EXITING ; 
#define  MSG_LOCK 130 
#define  MSG_SHUTDOWN 129 
#define  MSG_SUSPEND 128 
 int /*<<< orphan*/  MSG_UNLOCK ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 void* client_execcmd ; 
 void* client_execshell ; 
 int /*<<< orphan*/  client_exitreason ; 
 void* client_exitsession ; 
 int client_exittype ; 
 int client_exitval ; 
 int /*<<< orphan*/  client_peer ; 
 int /*<<< orphan*/  client_proc ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static void
client_dispatch_attached(struct imsg *imsg)
{
	struct sigaction	 sigact;
	char			*data;
	ssize_t			 datalen;

	data = imsg->data;
	datalen = imsg->hdr.len - IMSG_HEADER_SIZE;

	switch (imsg->hdr.type) {
	case MSG_DETACH:
	case MSG_DETACHKILL:
		if (datalen == 0 || data[datalen - 1] != '\0')
			fatalx("bad MSG_DETACH string");

		client_exitsession = xstrdup(data);
		client_exittype = imsg->hdr.type;
		if (imsg->hdr.type == MSG_DETACHKILL)
			client_exitreason = CLIENT_EXIT_DETACHED_HUP;
		else
			client_exitreason = CLIENT_EXIT_DETACHED;
		proc_send(client_peer, MSG_EXITING, -1, NULL, 0);
		break;
	case MSG_EXEC:
		if (datalen == 0 || data[datalen - 1] != '\0' ||
		    strlen(data) + 1 == (size_t)datalen)
			fatalx("bad MSG_EXEC string");
		client_execcmd = xstrdup(data);
		client_execshell = xstrdup(data + strlen(data) + 1);

		client_exittype = imsg->hdr.type;
		proc_send(client_peer, MSG_EXITING, -1, NULL, 0);
		break;
	case MSG_EXIT:
		if (datalen != 0 && datalen != sizeof (int))
			fatalx("bad MSG_EXIT size");

		proc_send(client_peer, MSG_EXITING, -1, NULL, 0);
		client_exitreason = CLIENT_EXIT_EXITED;
		break;
	case MSG_EXITED:
		if (datalen != 0)
			fatalx("bad MSG_EXITED size");

		proc_exit(client_proc);
		break;
	case MSG_SHUTDOWN:
		if (datalen != 0)
			fatalx("bad MSG_SHUTDOWN size");

		proc_send(client_peer, MSG_EXITING, -1, NULL, 0);
		client_exitreason = CLIENT_EXIT_SERVER_EXITED;
		client_exitval = 1;
		break;
	case MSG_SUSPEND:
		if (datalen != 0)
			fatalx("bad MSG_SUSPEND size");

		memset(&sigact, 0, sizeof sigact);
		sigemptyset(&sigact.sa_mask);
		sigact.sa_flags = SA_RESTART;
		sigact.sa_handler = SIG_DFL;
		if (sigaction(SIGTSTP, &sigact, NULL) != 0)
			fatal("sigaction failed");
		kill(getpid(), SIGTSTP);
		break;
	case MSG_LOCK:
		if (datalen == 0 || data[datalen - 1] != '\0')
			fatalx("bad MSG_LOCK string");

		system(data);
		proc_send(client_peer, MSG_UNLOCK, -1, NULL, 0);
		break;
	}
}