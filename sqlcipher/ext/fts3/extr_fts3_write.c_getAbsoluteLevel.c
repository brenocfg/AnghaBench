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
typedef  int sqlite3_int64 ;
struct TYPE_3__ {int nIndex; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int FTS3_SEGDIR_MAXLEVEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_fts3_nc (int) ; 

__attribute__((used)) static sqlite3_int64 getAbsoluteLevel(
  Fts3Table *p,                   /* FTS3 table handle */
  int iLangid,                    /* Language id */
  int iIndex,                     /* Index in p->aIndex[] */
  int iLevel                      /* Level of segments */
){
  sqlite3_int64 iBase;            /* First absolute level for iLangid/iIndex */
  assert_fts3_nc( iLangid>=0 );
  assert( p->nIndex>0 );
  assert( iIndex>=0 && iIndex<p->nIndex );

  iBase = ((sqlite3_int64)iLangid * p->nIndex + iIndex) * FTS3_SEGDIR_MAXLEVEL;
  return iBase + iLevel;
}