#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pVtab; } ;
struct TYPE_9__ {scalar_t__ iRowid; scalar_t__ iPos; scalar_t__ iEnd; scalar_t__ iStart; scalar_t__ nToken; scalar_t__ zToken; scalar_t__ zInput; scalar_t__ pCsr; TYPE_1__ base; } ;
struct TYPE_8__ {TYPE_2__* pMod; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* xClose ) (scalar_t__) ;} ;
typedef  TYPE_3__ Fts3tokTable ;
typedef  TYPE_4__ Fts3tokCursor ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void fts3tokResetCursor(Fts3tokCursor *pCsr){
  if( pCsr->pCsr ){
    Fts3tokTable *pTab = (Fts3tokTable *)(pCsr->base.pVtab);
    pTab->pMod->xClose(pCsr->pCsr);
    pCsr->pCsr = 0;
  }
  sqlite3_free(pCsr->zInput);
  pCsr->zInput = 0;
  pCsr->zToken = 0;
  pCsr->nToken = 0;
  pCsr->iStart = 0;
  pCsr->iEnd = 0;
  pCsr->iPos = 0;
  pCsr->iRowid = 0;
}