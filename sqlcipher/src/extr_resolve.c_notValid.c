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
struct TYPE_3__ {int ncFlags; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_1__ NameContext ;

/* Variables and functions */
 int NC_IdxExpr ; 
 int NC_IsCheck ; 
 int NC_PartIdx ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*,char const*,char const*) ; 

__attribute__((used)) static void notValid(
  Parse *pParse,       /* Leave error message here */
  NameContext *pNC,    /* The name context */
  const char *zMsg,    /* Type of error */
  int validMask        /* Set of contexts for which prohibited */
){
  assert( (validMask&~(NC_IsCheck|NC_PartIdx|NC_IdxExpr))==0 );
  if( (pNC->ncFlags & validMask)!=0 ){
    const char *zIn = "partial index WHERE clauses";
    if( pNC->ncFlags & NC_IdxExpr )      zIn = "index expressions";
#ifndef SQLITE_OMIT_CHECK
    else if( pNC->ncFlags & NC_IsCheck ) zIn = "CHECK constraints";
#endif
    sqlite3ErrorMsg(pParse, "%s prohibited in %s", zMsg, zIn);
  }
}