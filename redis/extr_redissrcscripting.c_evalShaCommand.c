#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_10__ {int /*<<< orphan*/  noscripterr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int CLIENT_LUA_DEBUG ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  evalGenericCommand (TYPE_2__*,int) ; 
 int sdslen (int /*<<< orphan*/ ) ; 
 TYPE_3__ shared ; 

void evalShaCommand(client *c) {
    if (sdslen(c->argv[1]->ptr) != 40) {
        /* We know that a match is not possible if the provided SHA is
         * not the right length. So we return an error ASAP, this way
         * evalGenericCommand() can be implemented without string length
         * sanity check */
        addReply(c, shared.noscripterr);
        return;
    }
    if (!(c->flags & CLIENT_LUA_DEBUG))
        evalGenericCommand(c,1);
    else {
        addReplyError(c,"Please use EVAL instead of EVALSHA for debugging");
        return;
    }
}