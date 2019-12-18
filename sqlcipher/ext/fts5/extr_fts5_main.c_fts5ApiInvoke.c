#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_6__ {int /*<<< orphan*/  (* xFunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ;} ;
struct TYPE_5__ {TYPE_2__* pAux; } ;
typedef  TYPE_1__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;
typedef  TYPE_2__ Fts5Auxiliary ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sFts5Api ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void fts5ApiInvoke(
  Fts5Auxiliary *pAux,
  Fts5Cursor *pCsr,
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  assert( pCsr->pAux==0 );
  pCsr->pAux = pAux;
  pAux->xFunc(&sFts5Api, (Fts5Context*)pCsr, context, argc, argv);
  pCsr->pAux = 0;
}