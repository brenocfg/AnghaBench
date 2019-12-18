#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* zToken; } ;
struct TYPE_10__ {scalar_t__ op; TYPE_1__ u; } ;
struct TYPE_9__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_8__ {char* zName; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_3__ ExprList ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 scalar_t__ TK_ID ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3StrICmp (char*,char*) ; 

__attribute__((used)) static int resolveAsName(
  Parse *pParse,     /* Parsing context for error messages */
  ExprList *pEList,  /* List of expressions to scan */
  Expr *pE           /* Expression we are trying to match */
){
  int i;             /* Loop counter */

  UNUSED_PARAMETER(pParse);

  if( pE->op==TK_ID ){
    char *zCol = pE->u.zToken;
    for(i=0; i<pEList->nExpr; i++){
      char *zAs = pEList->a[i].zName;
      if( zAs!=0 && sqlite3StrICmp(zAs, zCol)==0 ){
        return i+1;
      }
    }
  }
  return 0;
}