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
struct TYPE_6__ {scalar_t__ pStruct; scalar_t__ iStructVersion; } ;
typedef  TYPE_1__ Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts5IndexDataVersion (TYPE_1__*) ; 
 int fts5IndexReturn (TYPE_1__*) ; 
 int /*<<< orphan*/  fts5StructureInvalidate (TYPE_1__*) ; 

int sqlite3Fts5IndexReset(Fts5Index *p){
  assert( p->pStruct==0 || p->iStructVersion!=0 );
  if( fts5IndexDataVersion(p)!=p->iStructVersion ){
    fts5StructureInvalidate(p);
  }
  return fts5IndexReturn(p);
}