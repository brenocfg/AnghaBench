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
struct TYPE_8__ {scalar_t__ nHeight; scalar_t__ iRoot; } ;
struct TYPE_6__ {TYPE_3__ root; } ;
struct TYPE_7__ {TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;
typedef  TYPE_3__ TreeRoot ;

/* Variables and functions */
 int /*<<< orphan*/  dump_node_contents (TYPE_2__*,scalar_t__,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 

void dump_tree_contents(lsm_db *pDb, const char *zCaption){
  char zPath[64];
  TreeRoot *p = &pDb->treehdr.root;
  printf("\n%s\n", zCaption);
  zPath[0] = '/';
  if( p->iRoot ){
    dump_node_contents(pDb, p->iRoot, zPath, 1, p->nHeight-1);
  }
  fflush(stdout);
}