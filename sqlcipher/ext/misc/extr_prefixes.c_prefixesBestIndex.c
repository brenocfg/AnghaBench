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
struct sqlite3_index_constraint {int iColumn; scalar_t__ op; int /*<<< orphan*/  usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; double estimatedCost; int estimatedRows; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 

__attribute__((used)) static int prefixesBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  /* Search for a usable equality constraint against column 1 
  ** (original_string) and use it if at all possible */
  int i;
  const struct sqlite3_index_constraint *p;

  for(i=0, p=pIdxInfo->aConstraint; i<pIdxInfo->nConstraint; i++, p++){
    if( p->iColumn!=1 ) continue;
    if( p->op!=SQLITE_INDEX_CONSTRAINT_EQ ) continue;
    if( !p->usable ) continue;
    pIdxInfo->aConstraintUsage[i].argvIndex = 1;
    pIdxInfo->aConstraintUsage[i].omit = 1;
    pIdxInfo->estimatedCost = (double)10;
    pIdxInfo->estimatedRows = 10;
    return SQLITE_OK;
  }
  pIdxInfo->estimatedCost = (double)1000000000;
  pIdxInfo->estimatedRows = 1000000000;
  return SQLITE_OK;
}