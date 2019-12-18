#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_1__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */
 int sqlite3Fts5ExprPhraseSize (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fts5ApiPhraseSize(Fts5Context *pCtx, int iPhrase){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  return sqlite3Fts5ExprPhraseSize(pCsr->pExpr, iPhrase);
}