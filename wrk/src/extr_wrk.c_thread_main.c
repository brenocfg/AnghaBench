#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_9__ {int connections; TYPE_2__* cs; int /*<<< orphan*/  start; int /*<<< orphan*/ * loop; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ thread ;
struct TYPE_10__ {char* request; size_t length; int /*<<< orphan*/  delayed; int /*<<< orphan*/ * ssl; TYPE_1__* thread; } ;
typedef  TYPE_2__ connection ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_11__ {int /*<<< orphan*/  delay; scalar_t__ ctx; int /*<<< orphan*/  dynamic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECORD_INTERVAL_MS ; 
 int /*<<< orphan*/ * SSL_new (scalar_t__) ; 
 int /*<<< orphan*/  aeCreateTimeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aeDeleteEventLoop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aeMain (int /*<<< orphan*/ *) ; 
 TYPE_7__ cfg ; 
 int /*<<< orphan*/  connect_socket (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  record_rate ; 
 int /*<<< orphan*/  script_request (int /*<<< orphan*/ ,char**,size_t*) ; 
 int /*<<< orphan*/  time_us () ; 
 TYPE_2__* zcalloc (int) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void *thread_main(void *arg) {
    thread *thread = arg;

    char *request = NULL;
    size_t length = 0;

    if (!cfg.dynamic) {
        script_request(thread->L, &request, &length);
    }

    thread->cs = zcalloc(thread->connections * sizeof(connection));
    connection *c = thread->cs;

    for (uint64_t i = 0; i < thread->connections; i++, c++) {
        c->thread = thread;
        c->ssl     = cfg.ctx ? SSL_new(cfg.ctx) : NULL;
        c->request = request;
        c->length  = length;
        c->delayed = cfg.delay;
        connect_socket(thread, c);
    }

    aeEventLoop *loop = thread->loop;
    aeCreateTimeEvent(loop, RECORD_INTERVAL_MS, record_rate, thread, NULL);

    thread->start = time_us();
    aeMain(loop);

    aeDeleteEventLoop(loop);
    zfree(thread->cs);

    return NULL;
}