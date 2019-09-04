#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 TYPE_1__* getDecodedObject (TYPE_1__*) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xorDigest (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xorStringObjectDigest(unsigned char *digest, robj *o) {
    o = getDecodedObject(o);
    xorDigest(digest,o->ptr,sdslen(o->ptr));
    decrRefCount(o);
}