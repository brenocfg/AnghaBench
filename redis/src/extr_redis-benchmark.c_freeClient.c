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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
typedef  TYPE_1__* client ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_10__ {int requests; int /*<<< orphan*/  liveclients_mutex; scalar_t__ num_threads; int /*<<< orphan*/  clients; int /*<<< orphan*/  liveclients; int /*<<< orphan*/  requests_finished; } ;
struct TYPE_9__ {int /*<<< orphan*/  fd; } ;
struct TYPE_8__ {scalar_t__ thread_id; struct TYPE_8__* stagptr; struct TYPE_8__* randptr; int /*<<< orphan*/  obuf; TYPE_3__* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/ * CLIENT_GET_EVENTLOOP (TYPE_1__*) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aeStop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomicGet (int /*<<< orphan*/ ,int) ; 
 TYPE_6__ config ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redisFree (TYPE_3__*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

__attribute__((used)) static void freeClient(client c) {
    aeEventLoop *el = CLIENT_GET_EVENTLOOP(c);
    listNode *ln;
    aeDeleteFileEvent(el,c->context->fd,AE_WRITABLE);
    aeDeleteFileEvent(el,c->context->fd,AE_READABLE);
    if (c->thread_id >= 0) {
        int requests_finished = 0;
        atomicGet(config.requests_finished, requests_finished);
        if (requests_finished >= config.requests) {
            aeStop(el);
        }
    }
    redisFree(c->context);
    sdsfree(c->obuf);
    zfree(c->randptr);
    zfree(c->stagptr);
    zfree(c);
    if (config.num_threads) pthread_mutex_lock(&(config.liveclients_mutex));
    config.liveclients--;
    ln = listSearchKey(config.clients,c);
    assert(ln != NULL);
    listDelNode(config.clients,ln);
    if (config.num_threads) pthread_mutex_unlock(&(config.liveclients_mutex));
}