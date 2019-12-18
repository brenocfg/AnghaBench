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
struct TYPE_3__ {scalar_t__ eType; } ;
typedef  TYPE_1__ Fts3Expr ;

/* Variables and functions */
 scalar_t__ FTSQUERY_AND ; 
 scalar_t__ FTSQUERY_NEAR ; 
 scalar_t__ FTSQUERY_OR ; 
 scalar_t__ FTSQUERY_PHRASE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3_fts3_enable_parentheses ; 

__attribute__((used)) static int opPrecedence(Fts3Expr *p){
  assert( p->eType!=FTSQUERY_PHRASE );
  if( sqlite3_fts3_enable_parentheses ){
    return p->eType;
  }else if( p->eType==FTSQUERY_NEAR ){
    return 1;
  }else if( p->eType==FTSQUERY_OR ){
    return 2;
  }
  assert( p->eType==FTSQUERY_AND );
  return 3;
}