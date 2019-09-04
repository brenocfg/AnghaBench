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
typedef  int /*<<< orphan*/  stream ;
struct TYPE_4__ {int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_ENCODING_STREAM ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 TYPE_1__* createObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * streamNew () ; 

robj *createStreamObject(void) {
    stream *s = streamNew();
    robj *o = createObject(OBJ_STREAM,s);
    o->encoding = OBJ_ENCODING_STREAM;
    return o;
}