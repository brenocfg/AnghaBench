#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  TYPE_2__* client ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_10__ {int requests; int /*<<< orphan*/  slots_last_update; scalar_t__ cluster_mode; scalar_t__ randomkeys; int /*<<< orphan*/  requests_issued; } ;
struct TYPE_9__ {scalar_t__ written; scalar_t__ staglen; int latency; TYPE_1__* context; void* obuf; int /*<<< orphan*/  start; int /*<<< orphan*/  slots_last_update; } ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  aeCreateFileEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomicGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomicGetIncr (int /*<<< orphan*/ ,int,int) ; 
 TYPE_6__ config ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  freeClient (TYPE_2__*) ; 
 int /*<<< orphan*/  randomizeClientKey (TYPE_2__*) ; 
 int /*<<< orphan*/  readHandler ; 
 scalar_t__ sdslen (void*) ; 
 int /*<<< orphan*/  setClusterKeyHashTag (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  ustime () ; 
 int write (int /*<<< orphan*/ ,void*,scalar_t__) ; 

__attribute__((used)) static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    client c = privdata;
    UNUSED(el);
    UNUSED(fd);
    UNUSED(mask);

    /* Initialize request when nothing was written. */
    if (c->written == 0) {
        /* Enforce upper bound to number of requests. */
        int requests_issued = 0;
        atomicGetIncr(config.requests_issued, requests_issued, 1);
        if (requests_issued >= config.requests) {
            freeClient(c);
            return;
        }

        /* Really initialize: randomize keys and set start time. */
        if (config.randomkeys) randomizeClientKey(c);
        if (config.cluster_mode && c->staglen > 0) setClusterKeyHashTag(c);
        atomicGet(config.slots_last_update, c->slots_last_update);
        c->start = ustime();
        c->latency = -1;
    }
    if (sdslen(c->obuf) > c->written) {
        void *ptr = c->obuf+c->written;
        ssize_t nwritten = write(c->context->fd,ptr,sdslen(c->obuf)-c->written);
        if (nwritten == -1) {
            if (errno != EPIPE)
                fprintf(stderr, "Writing to socket: %s\n", strerror(errno));
            freeClient(c);
            return;
        }
        c->written += nwritten;
        if (sdslen(c->obuf) == c->written) {
            aeDeleteFileEvent(el,c->context->fd,AE_WRITABLE);
            aeCreateFileEvent(el,c->context->fd,AE_READABLE,readHandler,c);
        }
    }
}