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
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_10__ {scalar_t__ type; char* str; } ;
typedef  TYPE_2__ redisReply ;
typedef  TYPE_3__* client ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_13__ {int requests; scalar_t__* latency; int /*<<< orphan*/  requests_finished; scalar_t__ showerrors; } ;
struct TYPE_12__ {char* errstr; } ;
struct TYPE_11__ {scalar_t__ latency; scalar_t__ start; scalar_t__ pending; scalar_t__ prefix_pending; scalar_t__ prefixlen; size_t randlen; int /*<<< orphan*/ * randptr; int /*<<< orphan*/  obuf; TYPE_1__* cluster_node; scalar_t__ staglen; TYPE_4__* context; } ;
struct TYPE_9__ {char* ip; int port; } ;

/* Variables and functions */
 scalar_t__ REDIS_OK ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  atomicGetIncr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clientDone (TYPE_3__*) ; 
 TYPE_7__ config ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fetchClusterSlotsConfiguration (TYPE_3__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeReplyObject (void*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ redisBufferRead (TYPE_4__*) ; 
 scalar_t__ redisGetReply (TYPE_4__*,void**) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 scalar_t__ ustime () ; 

__attribute__((used)) static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    client c = privdata;
    void *reply = NULL;
    UNUSED(el);
    UNUSED(fd);
    UNUSED(mask);

    /* Calculate latency only for the first read event. This means that the
     * server already sent the reply and we need to parse it. Parsing overhead
     * is not part of the latency, so calculate it only once, here. */
    if (c->latency < 0) c->latency = ustime()-(c->start);

    if (redisBufferRead(c->context) != REDIS_OK) {
        fprintf(stderr,"Error: %s\n",c->context->errstr);
        exit(1);
    } else {
        while(c->pending) {
            if (redisGetReply(c->context,&reply) != REDIS_OK) {
                fprintf(stderr,"Error: %s\n",c->context->errstr);
                exit(1);
            }
            if (reply != NULL) {
                if (reply == (void*)REDIS_REPLY_ERROR) {
                    fprintf(stderr,"Unexpected error reply, exiting...\n");
                    exit(1);
                }
                redisReply *r = reply;
                int is_err = (r->type == REDIS_REPLY_ERROR);

                if (is_err && config.showerrors) {
                    /* TODO: static lasterr_time not thread-safe */
                    static time_t lasterr_time = 0;
                    time_t now = time(NULL);
                    if (lasterr_time != now) {
                        lasterr_time = now;
                        if (c->cluster_node) {
                            printf("Error from server %s:%d: %s\n",
                                   c->cluster_node->ip,
                                   c->cluster_node->port,
                                   r->str);
                        } else printf("Error from server: %s\n", r->str);
                    }
                }

                /* Try to update slots configuration if reply error is
                 * MOVED/ASK/CLUSTERDOWN and the key(s) used by the command
                 * contain(s) the slot hash tag. */
                if (is_err && c->cluster_node && c->staglen) {
                    int fetch_slots = 0, do_wait = 0;
                    if (!strncmp(r->str,"MOVED",5) || !strncmp(r->str,"ASK",3))
                        fetch_slots = 1;
                    else if (!strncmp(r->str,"CLUSTERDOWN",11)) {
                        /* Usually the cluster is able to recover itself after
                         * a CLUSTERDOWN error, so try to sleep one second
                         * before requesting the new configuration. */
                        fetch_slots = 1;
                        do_wait = 1;
                        printf("Error from server %s:%d: %s\n",
                               c->cluster_node->ip,
                               c->cluster_node->port,
                               r->str);
                    }
                    if (do_wait) sleep(1);
                    if (fetch_slots && !fetchClusterSlotsConfiguration(c))
                        exit(1);
                }

                freeReplyObject(reply);
                /* This is an OK for prefix commands such as auth and select.*/
                if (c->prefix_pending > 0) {
                    c->prefix_pending--;
                    c->pending--;
                    /* Discard prefix commands on first response.*/
                    if (c->prefixlen > 0) {
                        size_t j;
                        sdsrange(c->obuf, c->prefixlen, -1);
                        /* We also need to fix the pointers to the strings
                        * we need to randomize. */
                        for (j = 0; j < c->randlen; j++)
                            c->randptr[j] -= c->prefixlen;
                        c->prefixlen = 0;
                    }
                    continue;
                }
                int requests_finished = 0;
                atomicGetIncr(config.requests_finished, requests_finished, 1);
                if (requests_finished < config.requests)
                    config.latency[requests_finished] = c->latency;
                c->pending--;
                if (c->pending == 0) {
                    clientDone(c);
                    break;
                }
            } else {
                break;
            }
        }
    }
}