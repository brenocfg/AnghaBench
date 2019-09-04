#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  connect; } ;
struct TYPE_10__ {TYPE_2__ errors; struct aeEventLoop* loop; struct addrinfo* addr; } ;
typedef  TYPE_3__ thread ;
struct aeEventLoop {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  flags ;
struct TYPE_8__ {TYPE_4__* data; } ;
struct TYPE_11__ {int fd; TYPE_1__ parser; } ;
typedef  TYPE_4__ connection ;

/* Variables and functions */
 scalar_t__ AE_OK ; 
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 scalar_t__ aeCreateFileEvent (struct aeEventLoop*,int,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_connected ; 

__attribute__((used)) static int connect_socket(thread *thread, connection *c) {
    struct addrinfo *addr = thread->addr;
    struct aeEventLoop *loop = thread->loop;
    int fd, flags;

    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    if (connect(fd, addr->ai_addr, addr->ai_addrlen) == -1) {
        if (errno != EINPROGRESS) goto error;
    }

    flags = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(flags));

    flags = AE_READABLE | AE_WRITABLE;
    if (aeCreateFileEvent(loop, fd, flags, socket_connected, c) == AE_OK) {
        c->parser.data = c;
        c->fd = fd;
        return fd;
    }

  error:
    thread->errors.connect++;
    close(fd);
    return -1;
}