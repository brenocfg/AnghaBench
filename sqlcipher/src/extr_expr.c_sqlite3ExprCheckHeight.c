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
struct TYPE_6__ {TYPE_1__* db; } ;
struct TYPE_5__ {int* aLimit; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 size_t SQLITE_LIMIT_EXPR_DEPTH ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_2__*,char*,int) ; 

int sqlite3ExprCheckHeight(Parse *pParse, int nHeight){
  int rc = SQLITE_OK;
  int mxHeight = pParse->db->aLimit[SQLITE_LIMIT_EXPR_DEPTH];
  if( nHeight>mxHeight ){
    sqlite3ErrorMsg(pParse, 
       "Expression tree is too large (maximum depth %d)", mxHeight
    );
    rc = SQLITE_ERROR;
  }
  return rc;
}