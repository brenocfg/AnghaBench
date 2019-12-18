#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* pPhrase; } ;
struct TYPE_6__ {scalar_t__ nToken; } ;
struct TYPE_5__ {int /*<<< orphan*/  nToken; int /*<<< orphan*/  nPhrase; } ;
typedef  TYPE_1__ LoadDoclistCtx ;
typedef  TYPE_2__ Fts3Phrase ;
typedef  TYPE_3__ Fts3Expr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 

__attribute__((used)) static int fts3ExprLoadDoclistsCb(Fts3Expr *pExpr, int iPhrase, void *ctx){
  int rc = SQLITE_OK;
  Fts3Phrase *pPhrase = pExpr->pPhrase;
  LoadDoclistCtx *p = (LoadDoclistCtx *)ctx;

  UNUSED_PARAMETER(iPhrase);

  p->nPhrase++;
  p->nToken += pPhrase->nToken;

  return rc;
}