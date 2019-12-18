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
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct chmHttpSlave {int fd; struct chmHttpServer* server; } ;
struct chmHttpServer {int socket; int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  one ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  _slave ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/ * chm_open (char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 char* config_bind ; 
 int config_port ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  free (struct chmHttpSlave*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  listen (int,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void chmhttp_server(const char *filename)
{
    struct chmHttpServer        server;
    struct chmHttpSlave        *slave;
    struct sockaddr_in          bindAddr;
    int                         addrLen;
    pthread_t                   tid;
    int                         one = 1;

    /* open file */
    if ((server.file = chm_open(filename)) == NULL)
    {
        fprintf(stderr, "couldn't open file '%s'\n", filename);
        exit(2);
    }

    /* create socket */
    server.socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&bindAddr, 0, sizeof(struct sockaddr_in));
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_port = htons(config_port);
    bindAddr.sin_addr.s_addr = inet_addr(config_bind);

    if (setsockopt (server.socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one))) 
    {
        perror ("setsockopt");
        exit(3);
    }

    if (bind(server.socket, 
             (struct sockaddr *)&bindAddr,
             sizeof(struct sockaddr_in)) < 0)
    {
        close(server.socket);
        server.socket = -1;
        fprintf(stderr, "couldn't bind to ip %s port %d\n", config_bind, config_port);
        exit(3);
    }

    /* listen for connections */
    listen(server.socket, 75);
    addrLen = sizeof(struct sockaddr);
    while(1)
    {
        slave = (struct chmHttpSlave *)malloc(sizeof(struct chmHttpSlave));
        slave->server = &server;
        slave->fd = accept(server.socket, (struct sockaddr *)&bindAddr, &addrLen);
        if (slave->fd == -1)
            break;

        pthread_create(&tid, NULL, _slave, (void *)slave);
        pthread_detach(tid);
    }
    free(slave);
}