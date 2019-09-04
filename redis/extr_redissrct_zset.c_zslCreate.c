#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int level; int /*<<< orphan*/ * tail; TYPE_3__* header; scalar_t__ length; } ;
typedef  TYPE_2__ zskiplist ;
struct TYPE_8__ {int /*<<< orphan*/ * backward; TYPE_1__* level; } ;
struct TYPE_6__ {scalar_t__ span; int /*<<< orphan*/ * forward; } ;

/* Variables and functions */
 int ZSKIPLIST_MAXLEVEL ; 
 TYPE_2__* zmalloc (int) ; 
 TYPE_3__* zslCreateNode (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

zskiplist *zslCreate(void) {
    int j;
    zskiplist *zsl;

    zsl = zmalloc(sizeof(*zsl));
    zsl->level = 1;
    zsl->length = 0;
    zsl->header = zslCreateNode(ZSKIPLIST_MAXLEVEL,0,NULL);
    for (j = 0; j < ZSKIPLIST_MAXLEVEL; j++) {
        zsl->header->level[j].forward = NULL;
        zsl->header->level[j].span = 0;
    }
    zsl->header->backward = NULL;
    zsl->tail = NULL;
    return zsl;
}