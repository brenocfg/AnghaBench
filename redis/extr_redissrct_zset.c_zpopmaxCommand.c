#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int argc; int /*<<< orphan*/ ** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZSET_MAX ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genericZpopCommand (TYPE_1__*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__ shared ; 

void zpopmaxCommand(client *c) {
    if (c->argc > 3) {
        addReply(c,shared.syntaxerr);
        return;
    }
    genericZpopCommand(c,&c->argv[1],1,ZSET_MAX,0,
        c->argc == 3 ? c->argv[2] : NULL);
}