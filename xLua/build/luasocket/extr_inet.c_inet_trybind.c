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
typedef  scalar_t__ t_socket ;
struct addrinfo {scalar_t__ ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  scalar_t__* p_socket ;
typedef  int /*<<< orphan*/  SA ;

/* Variables and functions */
 scalar_t__ SOCKET_INVALID ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  socket_bind (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_create (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_destroy (scalar_t__*) ; 
 char* socket_gaistrerror (int /*<<< orphan*/ ) ; 
 char* socket_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

const char *inet_trybind(p_socket ps, const char *address, const char *serv,
        struct addrinfo *bindhints)
{
    struct addrinfo *iterator = NULL, *resolved = NULL;
    const char *err = NULL;
    t_socket sock = *ps;
    /* translate luasocket special values to C */
    if (strcmp(address, "*") == 0) address = NULL;
    if (!serv) serv = "0";
    /* try resolving */
    err = socket_gaistrerror(getaddrinfo(address, serv, bindhints, &resolved));
    if (err) {
        if (resolved) freeaddrinfo(resolved);
        return err;
    }
    /* iterate over resolved addresses until one is good */
    for (iterator = resolved; iterator; iterator = iterator->ai_next) {
        if(sock == SOCKET_INVALID) {
            err = socket_strerror(socket_create(&sock, iterator->ai_family,
                        iterator->ai_socktype, iterator->ai_protocol));
            if(err)
                continue;
        }
        /* try binding to local address */
        err = socket_strerror(socket_bind(&sock,
            (SA *) iterator->ai_addr,
            (socklen_t) iterator->ai_addrlen));

        /* keep trying unless bind succeeded */
        if (err) {
            if(sock != *ps)
                socket_destroy(&sock);
        } else {
            /* remember what we connected to, particularly the family */
            *bindhints = *iterator;
            break;
        }
    }
    /* cleanup and return error */
    freeaddrinfo(resolved);
    *ps = sock;
    return err;
}