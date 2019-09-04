#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ redisContext ;
struct TYPE_6__ {TYPE_4__* data; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  delWrite; int /*<<< orphan*/  addWrite; int /*<<< orphan*/  delRead; int /*<<< orphan*/  addRead; } ;
struct TYPE_8__ {TYPE_1__ ev; TYPE_2__ c; } ;
typedef  TYPE_3__ redisAsyncContext ;
struct TYPE_9__ {scalar_t__ writing; scalar_t__ reading; int /*<<< orphan*/  fd; int /*<<< orphan*/ * loop; TYPE_3__* context; } ;
typedef  TYPE_4__ redisAeEvents ;
typedef  int /*<<< orphan*/  aeEventLoop ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  redisAeAddRead ; 
 int /*<<< orphan*/  redisAeAddWrite ; 
 int /*<<< orphan*/  redisAeCleanup ; 
 int /*<<< orphan*/  redisAeDelRead ; 
 int /*<<< orphan*/  redisAeDelWrite ; 
 scalar_t__ zmalloc (int) ; 

__attribute__((used)) static int redisAeAttach(aeEventLoop *loop, redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    redisAeEvents *e;

    /* Nothing should be attached when something is already attached */
    if (ac->ev.data != NULL)
        return C_ERR;

    /* Create container for context and r/w events */
    e = (redisAeEvents*)zmalloc(sizeof(*e));
    e->context = ac;
    e->loop = loop;
    e->fd = c->fd;
    e->reading = e->writing = 0;

    /* Register functions to start/stop listening for events */
    ac->ev.addRead = redisAeAddRead;
    ac->ev.delRead = redisAeDelRead;
    ac->ev.addWrite = redisAeAddWrite;
    ac->ev.delWrite = redisAeDelWrite;
    ac->ev.cleanup = redisAeCleanup;
    ac->ev.data = e;

    return C_OK;
}