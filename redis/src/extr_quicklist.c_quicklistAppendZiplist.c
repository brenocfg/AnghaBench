#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* zl; scalar_t__ count; int /*<<< orphan*/  sz; } ;
typedef  TYPE_1__ quicklistNode ;
struct TYPE_8__ {int /*<<< orphan*/  count; int /*<<< orphan*/  tail; } ;
typedef  TYPE_2__ quicklist ;

/* Variables and functions */
 int /*<<< orphan*/  _quicklistInsertNodeAfter (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* quicklistCreateNode () ; 
 int /*<<< orphan*/  ziplistBlobLen (unsigned char*) ; 
 scalar_t__ ziplistLen (unsigned char*) ; 

void quicklistAppendZiplist(quicklist *quicklist, unsigned char *zl) {
    quicklistNode *node = quicklistCreateNode();

    node->zl = zl;
    node->count = ziplistLen(node->zl);
    node->sz = ziplistBlobLen(zl);

    _quicklistInsertNodeAfter(quicklist, quicklist->tail, node);
    quicklist->count += node->count;
}