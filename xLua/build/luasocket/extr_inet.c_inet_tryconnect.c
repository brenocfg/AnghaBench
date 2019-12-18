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
struct addrinfo {int ai_family; scalar_t__ ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  p_timeout ;
typedef  int /*<<< orphan*/  p_socket ;
typedef  int /*<<< orphan*/  SA ;

/* Variables and functions */
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  socket_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_destroy (int /*<<< orphan*/ ) ; 
 char* socket_gaistrerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_setnonblocking (int /*<<< orphan*/ ) ; 
 char* socket_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ ) ; 

const char *inet_tryconnect(p_socket ps, int *family, const char *address,
        const char *serv, p_timeout tm, struct addrinfo *connecthints)
{
    struct addrinfo *iterator = NULL, *resolved = NULL;
    const char *err = NULL;
    /* try resolving */
    err = socket_gaistrerror(getaddrinfo(address, serv,
                connecthints, &resolved));
    if (err != NULL) {
        if (resolved) freeaddrinfo(resolved);
        return err;
    }
    for (iterator = resolved; iterator; iterator = iterator->ai_next) {
        timeout_markstart(tm);
        /* create new socket if necessary. if there was no
         * bind, we need to create one for every new family
         * that shows up while iterating. if there was a
         * bind, all families will be the same and we will
         * not enter this branch. */
        if (*family != iterator->ai_family) {
            socket_destroy(ps);
            err = socket_strerror(socket_create(ps, iterator->ai_family, 
                iterator->ai_socktype, iterator->ai_protocol));
            if (err != NULL) {
                freeaddrinfo(resolved);
                return err;
            }
            *family = iterator->ai_family;
            /* all sockets initially non-blocking */
            socket_setnonblocking(ps);
        }
        /* try connecting to remote address */
        err = socket_strerror(socket_connect(ps, (SA *) iterator->ai_addr, 
            (socklen_t) iterator->ai_addrlen, tm));
        /* if success, break out of loop */
        if (err == NULL) break;
    }
    freeaddrinfo(resolved);
    /* here, if err is set, we failed */
    return err;
}