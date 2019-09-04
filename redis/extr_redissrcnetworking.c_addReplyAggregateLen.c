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
typedef  int /*<<< orphan*/  client ;
struct TYPE_2__ {int /*<<< orphan*/ * mbulkhdr; } ;

/* Variables and functions */
 long OBJ_SHARED_BULKHDR_LEN ; 
 int /*<<< orphan*/  addReply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyLongLongWithPrefix (int /*<<< orphan*/ *,long,int) ; 
 TYPE_1__ shared ; 

void addReplyAggregateLen(client *c, long length, int prefix) {
    if (prefix == '*' && length < OBJ_SHARED_BULKHDR_LEN)
        addReply(c,shared.mbulkhdr[length]);
    else
        addReplyLongLongWithPrefix(c,length,prefix);
}