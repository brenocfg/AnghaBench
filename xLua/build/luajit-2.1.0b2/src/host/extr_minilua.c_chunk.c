#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  token; } ;
struct TYPE_11__ {TYPE_2__* fs; TYPE_1__ t; } ;
struct TYPE_10__ {int /*<<< orphan*/  nactvar; int /*<<< orphan*/  freereg; } ;
typedef  TYPE_3__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  block_follow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enterlevel (TYPE_3__*) ; 
 int /*<<< orphan*/  leavelevel (TYPE_3__*) ; 
 int statement (TYPE_3__*) ; 
 int /*<<< orphan*/  testnext (TYPE_3__*,char) ; 

__attribute__((used)) static void chunk(LexState*ls){
int islast=0;
enterlevel(ls);
while(!islast&&!block_follow(ls->t.token)){
islast=statement(ls);
testnext(ls,';');
ls->fs->freereg=ls->fs->nactvar;
}
leavelevel(ls);
}