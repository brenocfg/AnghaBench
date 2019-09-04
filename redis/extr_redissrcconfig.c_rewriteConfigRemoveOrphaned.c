#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rewriteConfigState {int /*<<< orphan*/ * lines; int /*<<< orphan*/  rewritten; int /*<<< orphan*/  option_to_line; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_4__ {scalar_t__ value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* listFirst (int /*<<< orphan*/ *) ; 
 scalar_t__ listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
    dictIterator *di = dictGetIterator(state->option_to_line);
    dictEntry *de;

    while((de = dictNext(di)) != NULL) {
        list *l = dictGetVal(de);
        sds option = dictGetKey(de);

        /* Don't blank lines about options the rewrite process
         * don't understand. */
        if (dictFind(state->rewritten,option) == NULL) {
            serverLog(LL_DEBUG,"Not rewritten option: %s", option);
            continue;
        }

        while(listLength(l)) {
            listNode *ln = listFirst(l);
            int linenum = (long) ln->value;

            sdsfree(state->lines[linenum]);
            state->lines[linenum] = sdsempty();
            listDelNode(l,ln);
        }
    }
    dictReleaseIterator(di);
}