#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  streamID ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int streamGenericParseIDOrReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int streamParseIDOrReply(client *c, robj *o, streamID *id, uint64_t missing_seq) {
    return streamGenericParseIDOrReply(c,o,id,missing_seq,0);
}