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
typedef  int /*<<< orphan*/  Fts3Expr ;

/* Variables and functions */
 int /*<<< orphan*/  fts3ExprIterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  fts3ExprPhraseCountCb ; 

__attribute__((used)) static int fts3ExprPhraseCount(Fts3Expr *pExpr){
  int nPhrase = 0;
  (void)fts3ExprIterate(pExpr, fts3ExprPhraseCountCb, (void *)&nPhrase);
  return nPhrase;
}