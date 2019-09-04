#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {int argc; size_t resp; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_11__ {int /*<<< orphan*/ * null; int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 int OBJ_ENCODING_INTSET ; 
 int /*<<< orphan*/  OBJ_SET ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookupKeyReadOrReply (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int setTypeRandomElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  srandmemberWithCountCommand (TYPE_1__*) ; 

void srandmemberCommand(client *c) {
    robj *set;
    sds ele;
    int64_t llele;
    int encoding;

    if (c->argc == 3) {
        srandmemberWithCountCommand(c);
        return;
    } else if (c->argc > 3) {
        addReply(c,shared.syntaxerr);
        return;
    }

    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.null[c->resp]))
        == NULL || checkType(c,set,OBJ_SET)) return;

    encoding = setTypeRandomElement(set,&ele,&llele);
    if (encoding == OBJ_ENCODING_INTSET) {
        addReplyBulkLongLong(c,llele);
    } else {
        addReplyBulkCBuffer(c,ele,sdslen(ele));
    }
}