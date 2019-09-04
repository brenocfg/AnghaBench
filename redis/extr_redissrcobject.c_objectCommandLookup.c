#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ robj ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_9__ {TYPE_1__* db; } ;
typedef  TYPE_3__ client ;
struct TYPE_7__ {int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dictGetVal (int /*<<< orphan*/ *) ; 

robj *objectCommandLookup(client *c, robj *key) {
    dictEntry *de;

    if ((de = dictFind(c->db->dict,key->ptr)) == NULL) return NULL;
    return (robj*) dictGetVal(de);
}