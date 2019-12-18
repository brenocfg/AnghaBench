#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pAllVtab; struct TYPE_3__* pMod; struct TYPE_3__* zName; int /*<<< orphan*/  (* xChildDestroy ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  pChildAux; int /*<<< orphan*/  bDisposed; } ;
typedef  TYPE_1__ vtshim_aux ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vtshimAuxDestructor(void *pXAux){
  vtshim_aux *pAux = (vtshim_aux*)pXAux;
  assert( pAux->pAllVtab==0 );
  if( !pAux->bDisposed && pAux->xChildDestroy ){
    pAux->xChildDestroy(pAux->pChildAux);
    pAux->xChildDestroy = 0;
  }
  sqlite3_free(pAux->zName);
  sqlite3_free(pAux->pMod);
  sqlite3_free(pAux);
}