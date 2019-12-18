#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  mDbFlags; TYPE_2__* aDb; } ;
typedef  TYPE_4__ sqlite3 ;
struct TYPE_16__ {struct TYPE_16__* pNext; TYPE_3__* pTable; } ;
struct TYPE_14__ {TYPE_5__* pIndex; } ;
struct TYPE_13__ {TYPE_1__* pSchema; } ;
struct TYPE_12__ {int /*<<< orphan*/  idxHash; } ;
typedef  TYPE_5__ Index ;
typedef  int /*<<< orphan*/  Hash ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_5__*) ; 
 int /*<<< orphan*/  DBFLAG_SchemaChange ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3FreeIndex (TYPE_4__*,TYPE_5__*) ; 
 TYPE_5__* sqlite3HashInsert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SchemaMutexHeld (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

void sqlite3UnlinkAndDeleteIndex(sqlite3 *db, int iDb, const char *zIdxName){
  Index *pIndex;
  Hash *pHash;

  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
  pHash = &db->aDb[iDb].pSchema->idxHash;
  pIndex = sqlite3HashInsert(pHash, zIdxName, 0);
  if( ALWAYS(pIndex) ){
    if( pIndex->pTable->pIndex==pIndex ){
      pIndex->pTable->pIndex = pIndex->pNext;
    }else{
      Index *p;
      /* Justification of ALWAYS();  The index must be on the list of
      ** indices. */
      p = pIndex->pTable->pIndex;
      while( ALWAYS(p) && p->pNext!=pIndex ){ p = p->pNext; }
      if( ALWAYS(p && p->pNext==pIndex) ){
        p->pNext = pIndex->pNext;
      }
    }
    sqlite3FreeIndex(db, pIndex);
  }
  db->mDbFlags |= DBFLAG_SchemaChange;
}