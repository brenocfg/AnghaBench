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
typedef  int /*<<< orphan*/  raxNode ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** raxNodeFirstChildPtr (int /*<<< orphan*/ *) ; 

raxNode **raxFindParentLink(raxNode *parent, raxNode *child) {
    raxNode **cp = raxNodeFirstChildPtr(parent);
    raxNode *c;
    while(1) {
        memcpy(&c,cp,sizeof(c));
        if (c == child) break;
        cp++;
    }
    return cp;
}