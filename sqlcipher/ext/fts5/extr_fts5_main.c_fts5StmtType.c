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
struct TYPE_3__ {scalar_t__ ePlan; scalar_t__ bDesc; } ;
typedef  TYPE_1__ Fts5Cursor ;

/* Variables and functions */
 scalar_t__ FTS5_PLAN_SCAN ; 
 int FTS5_STMT_LOOKUP ; 
 int FTS5_STMT_SCAN_ASC ; 
 int FTS5_STMT_SCAN_DESC ; 

__attribute__((used)) static int fts5StmtType(Fts5Cursor *pCsr){
  if( pCsr->ePlan==FTS5_PLAN_SCAN ){
    return (pCsr->bDesc) ? FTS5_STMT_SCAN_DESC : FTS5_STMT_SCAN_ASC;
  }
  return FTS5_STMT_LOOKUP;
}