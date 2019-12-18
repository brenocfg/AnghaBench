#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* thread; scalar_t__ written; int /*<<< orphan*/  parser; } ;
typedef  TYPE_2__ connection ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_13__ {int /*<<< orphan*/  host; } ;
struct TYPE_9__ {int /*<<< orphan*/  connect; } ;
struct TYPE_12__ {TYPE_1__ errors; int /*<<< orphan*/  loop; } ;
struct TYPE_11__ {int (* connect ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
#define  ERROR 130 
 int /*<<< orphan*/  HTTP_RESPONSE ; 
#define  OK 129 
#define  RETRY 128 
 int /*<<< orphan*/  aeCreateFileEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_7__ cfg ; 
 int /*<<< orphan*/  http_parser_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reconnect_socket (TYPE_5__*,TYPE_2__*) ; 
 TYPE_4__ sock ; 
 int /*<<< orphan*/  socket_readable ; 
 int /*<<< orphan*/  socket_writeable ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_connected(aeEventLoop *loop, int fd, void *data, int mask) {
    connection *c = data;

    switch (sock.connect(c, cfg.host)) {
        case OK:    break;
        case ERROR: goto error;
        case RETRY: return;
    }

    http_parser_init(&c->parser, HTTP_RESPONSE);
    c->written = 0;

    aeCreateFileEvent(c->thread->loop, fd, AE_READABLE, socket_readable, c);
    aeCreateFileEvent(c->thread->loop, fd, AE_WRITABLE, socket_writeable, c);

    return;

  error:
    c->thread->errors.connect++;
    reconnect_socket(c->thread, c);
}