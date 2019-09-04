#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_9__ {TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_8__ {scalar_t__ ptr; } ;

/* Variables and functions */
 void* addReplyDeferredLen (TYPE_2__*) ; 
 int /*<<< orphan*/  addReplyStatus (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  addReplyStatusFormat (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  sdstoupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setDeferredArrayLen (TYPE_2__*,void*,int) ; 

void addReplyHelp(client *c, const char **help) {
    sds cmd = sdsnew((char*) c->argv[0]->ptr);
    void *blenp = addReplyDeferredLen(c);
    int blen = 0;

    sdstoupper(cmd);
    addReplyStatusFormat(c,
        "%s <subcommand> arg arg ... arg. Subcommands are:",cmd);
    sdsfree(cmd);

    while (help[blen]) addReplyStatus(c,help[blen++]);

    blen++;  /* Account for the header line(s). */
    setDeferredArrayLen(c,blenp,blen);
}