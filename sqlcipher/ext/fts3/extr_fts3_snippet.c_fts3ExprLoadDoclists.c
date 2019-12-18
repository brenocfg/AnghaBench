#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pExpr; } ;
struct TYPE_4__ {int nPhrase; int nToken; TYPE_2__* pCsr; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ LoadDoclistCtx ;
typedef  TYPE_2__ Fts3Cursor ;

/* Variables and functions */
 int fts3ExprIterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  fts3ExprLoadDoclistsCb ; 

__attribute__((used)) static int fts3ExprLoadDoclists(
  Fts3Cursor *pCsr,               /* Fts3 cursor for current query */
  int *pnPhrase,                  /* OUT: Number of phrases in query */
  int *pnToken                    /* OUT: Number of tokens in query */
){
  int rc;                         /* Return Code */
  LoadDoclistCtx sCtx = {0,0,0};  /* Context for fts3ExprIterate() */
  sCtx.pCsr = pCsr;
  rc = fts3ExprIterate(pCsr->pExpr, fts3ExprLoadDoclistsCb, (void *)&sCtx);
  if( pnPhrase ) *pnPhrase = sCtx.nPhrase;
  if( pnToken ) *pnToken = sCtx.nToken;
  return rc;
}