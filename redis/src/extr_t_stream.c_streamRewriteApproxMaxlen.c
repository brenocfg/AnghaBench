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
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ stream ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/ * createStringObject (char*,int) ; 
 int /*<<< orphan*/ * createStringObjectFromLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewriteClientCommandArgument (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void streamRewriteApproxMaxlen(client *c, stream *s, int maxlen_arg_idx) {
    robj *maxlen_obj = createStringObjectFromLongLong(s->length);
    robj *equal_obj = createStringObject("=",1);

    rewriteClientCommandArgument(c,maxlen_arg_idx,maxlen_obj);
    rewriteClientCommandArgument(c,maxlen_arg_idx-1,equal_obj);

    decrRefCount(equal_obj);
    decrRefCount(maxlen_obj);
}