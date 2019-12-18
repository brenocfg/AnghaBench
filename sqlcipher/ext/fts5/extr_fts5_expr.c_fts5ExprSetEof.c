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
struct TYPE_3__ {int bEof; int nChild; struct TYPE_3__** apChild; scalar_t__ bNomatch; } ;
typedef  TYPE_1__ Fts5ExprNode ;

/* Variables and functions */

__attribute__((used)) static void fts5ExprSetEof(Fts5ExprNode *pNode){
  int i;
  pNode->bEof = 1;
  pNode->bNomatch = 0;
  for(i=0; i<pNode->nChild; i++){
    fts5ExprSetEof(pNode->apChild[i]);
  }
}