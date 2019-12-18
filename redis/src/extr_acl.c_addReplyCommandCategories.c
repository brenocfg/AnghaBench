#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct redisCommand {int flags; } ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_2__ {int flag; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* ACLCommandCategories ; 
 void* addReplyDeferredLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyStatusFormat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setDeferredSetLen (int /*<<< orphan*/ *,void*,int) ; 

void addReplyCommandCategories(client *c, struct redisCommand *cmd) {
    int flagcount = 0;
    void *flaglen = addReplyDeferredLen(c);
    for (int j = 0; ACLCommandCategories[j].flag != 0; j++) {
        if (cmd->flags & ACLCommandCategories[j].flag) {
            addReplyStatusFormat(c, "@%s", ACLCommandCategories[j].name);
            flagcount++;
        }
    }
    setDeferredSetLen(c, flaglen, flagcount);
}