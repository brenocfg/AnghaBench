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
struct sockaddr_un {int sin_port; int /*<<< orphan*/  sun_path; void* sun_family; int /*<<< orphan*/  sin_addr; void* sin_family; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  server ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  XtPointer ;
typedef  int /*<<< orphan*/  XtAppContext ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_UNIX ; 
 int BUFSIZ ; 
 scalar_t__ ECONNREFUSED ; 
 int /*<<< orphan*/  NOCATGETS (char*) ; 
 int /*<<< orphan*/  PERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROTOCOL_VERSION ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  XtAppAddInput (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ XtInputReadMask ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/ * dfd ; 
 int /*<<< orphan*/  dummy ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 struct hostent* gethostbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inputHandler ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  messageFromEserve ; 
 int sd ; 
 int socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  vim_memset (char*,char,int) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  workshop_get_editor_name () ; 
 int /*<<< orphan*/  workshop_get_editor_version () ; 
 int /*<<< orphan*/  write (int,char*,int /*<<< orphan*/ ) ; 

void	workshop_connect(XtAppContext context)
{
#ifdef INET_SOCKETS
	struct sockaddr_in	server;
	struct hostent *	host;
	int			port;
#else
	struct sockaddr_un	server;
#endif
	char			buf[32];
	char *			address;
#ifdef DEBUG
	char			*file;
#endif

	address = getenv(NOCATGETS("SPRO_EDITOR_SOCKET"));
	if (address == NULL) {
		return;
	}

#ifdef INET_SOCKETS
	port = atoi(address);

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		PERROR(NOCATGETS("workshop_connect"));
		return;
	}

	/* Get the server internet address and put into addr structure */
	/* fill in the socket address structure and connect to server */
	vim_memset((char *)&server, '\0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = port;
	if ((host = gethostbyname(NOCATGETS("localhost"))) == NULL) {
		PERROR(NOCATGETS("gethostbyname"));
		sd = -1;
		return;
	}
	memcpy((char *)&server.sin_addr, host->h_addr, host->h_length);
#else
	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		PERROR(NOCATGETS("workshop_connect"));
		return;
	}

	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, address);
#endif
	/* Connect to server */
	if (connect(sd, (struct sockaddr *)&server, sizeof(server))) {
		if (errno == ECONNREFUSED) {
			close(sd);
#ifdef INET_SOCKETS
			if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
				PERROR(NOCATGETS("workshop_connect"));
				return;
			}
#else
			if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
				PERROR(NOCATGETS("workshop_connect"));
				return;
			}
#endif
			if (connect(sd, (struct sockaddr *)&server,
						sizeof(server))) {
				PERROR(NOCATGETS("workshop_connect"));
				return;
			}

		} else {
			PERROR(NOCATGETS("workshop_connect"));
			return;
		}
	}

	/* tell notifier we are interested in being called
	 * when there is input on the editor connection socket
	 */
	inputHandler = XtAppAddInput(context, sd, (XtPointer) XtInputReadMask,
				     messageFromEserve, NULL);
#ifdef DEBUG
	if ((file = getenv(NOCATGETS("SPRO_PLUGIN_DEBUG"))) != NULL) {
		char buf[BUFSIZ];

		unlink(file);
		vim_snprintf(buf, sizeof(buf), "date > %s", file);
		system(buf);
		dfd = fopen(file, "a");
	} else {
		dfd = NULL;
	}
#endif

	vim_snprintf(buf, sizeof(buf), NOCATGETS("connected %s %s %s\n"),
		workshop_get_editor_name(),
		PROTOCOL_VERSION,
		workshop_get_editor_version());
	dummy = write(sd, buf, strlen(buf));

	vim_snprintf(buf, sizeof(buf), NOCATGETS("ack 1\n"));
	dummy = write(sd, buf, strlen(buf));
}