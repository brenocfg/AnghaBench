#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ynVar ;
typedef  scalar_t__ u32 ;
struct TYPE_11__ {int* aLimit; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int i64 ;
struct TYPE_10__ {char* zToken; } ;
struct TYPE_13__ {int iColumn; TYPE_1__ u; } ;
struct TYPE_12__ {int nVar; int /*<<< orphan*/  pVList; TYPE_2__* db; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int EP_IntValue ; 
 int EP_Reduced ; 
 int EP_TokenOnly ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_4__*,int) ; 
 size_t SQLITE_LIMIT_VARIABLE_NUMBER ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3Atoi64 (char const*,int*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_3__*,char*,...) ; 
 scalar_t__ sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3VListAdd (TYPE_2__*,int /*<<< orphan*/ ,char const*,scalar_t__,int) ; 
 scalar_t__ sqlite3VListNameToNum (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ sqlite3VListNumToName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

void sqlite3ExprAssignVarNumber(Parse *pParse, Expr *pExpr, u32 n){
  sqlite3 *db = pParse->db;
  const char *z;
  ynVar x;

  if( pExpr==0 ) return;
  assert( !ExprHasProperty(pExpr, EP_IntValue|EP_Reduced|EP_TokenOnly) );
  z = pExpr->u.zToken;
  assert( z!=0 );
  assert( z[0]!=0 );
  assert( n==(u32)sqlite3Strlen30(z) );
  if( z[1]==0 ){
    /* Wildcard of the form "?".  Assign the next variable number */
    assert( z[0]=='?' );
    x = (ynVar)(++pParse->nVar);
  }else{
    int doAdd = 0;
    if( z[0]=='?' ){
      /* Wildcard of the form "?nnn".  Convert "nnn" to an integer and
      ** use it as the variable number */
      i64 i;
      int bOk;
      if( n==2 ){ /*OPTIMIZATION-IF-TRUE*/
        i = z[1]-'0';  /* The common case of ?N for a single digit N */
        bOk = 1;
      }else{
        bOk = 0==sqlite3Atoi64(&z[1], &i, n-1, SQLITE_UTF8);
      }
      testcase( i==0 );
      testcase( i==1 );
      testcase( i==db->aLimit[SQLITE_LIMIT_VARIABLE_NUMBER]-1 );
      testcase( i==db->aLimit[SQLITE_LIMIT_VARIABLE_NUMBER] );
      if( bOk==0 || i<1 || i>db->aLimit[SQLITE_LIMIT_VARIABLE_NUMBER] ){
        sqlite3ErrorMsg(pParse, "variable number must be between ?1 and ?%d",
            db->aLimit[SQLITE_LIMIT_VARIABLE_NUMBER]);
        return;
      }
      x = (ynVar)i;
      if( x>pParse->nVar ){
        pParse->nVar = (int)x;
        doAdd = 1;
      }else if( sqlite3VListNumToName(pParse->pVList, x)==0 ){
        doAdd = 1;
      }
    }else{
      /* Wildcards like ":aaa", "$aaa" or "@aaa".  Reuse the same variable
      ** number as the prior appearance of the same name, or if the name
      ** has never appeared before, reuse the same variable number
      */
      x = (ynVar)sqlite3VListNameToNum(pParse->pVList, z, n);
      if( x==0 ){
        x = (ynVar)(++pParse->nVar);
        doAdd = 1;
      }
    }
    if( doAdd ){
      pParse->pVList = sqlite3VListAdd(db, pParse->pVList, z, n, x);
    }
  }
  pExpr->iColumn = x;
  if( x>db->aLimit[SQLITE_LIMIT_VARIABLE_NUMBER] ){
    sqlite3ErrorMsg(pParse, "too many SQL variables");
  }
}