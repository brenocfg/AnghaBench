#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int reading; int /*<<< orphan*/  fd; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ redisAeEvents ;
typedef  int /*<<< orphan*/  aeEventLoop ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  aeCreateFileEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  redisAeReadEvent ; 

__attribute__((used)) static void redisAeAddRead(void *privdata) {
    redisAeEvents *e = (redisAeEvents*)privdata;
    aeEventLoop *loop = e->loop;
    if (!e->reading) {
        e->reading = 1;
        aeCreateFileEvent(loop,e->fd,AE_READABLE,redisAeReadEvent,e);
    }
}