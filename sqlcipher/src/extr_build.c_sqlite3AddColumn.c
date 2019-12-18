#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int* aLimit; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_25__ {size_t n; int /*<<< orphan*/  z; } ;
typedef  TYPE_3__ Token ;
struct TYPE_26__ {int nCol; char* zName; TYPE_6__* aCol; } ;
typedef  TYPE_4__ Table ;
struct TYPE_29__ {int szSorterRef; } ;
struct TYPE_28__ {char* zName; int szEst; int /*<<< orphan*/  colFlags; int /*<<< orphan*/  affinity; } ;
struct TYPE_23__ {scalar_t__ n; } ;
struct TYPE_27__ {TYPE_1__ constraintName; TYPE_4__* pNewTable; TYPE_2__* db; } ;
typedef  TYPE_5__ Parse ;
typedef  TYPE_6__ Column ;

/* Variables and functions */
 int /*<<< orphan*/  COLFLAG_HASTYPE ; 
 int /*<<< orphan*/  COLFLAG_SORTERREF ; 
 scalar_t__ IN_RENAME_OBJECT ; 
 int /*<<< orphan*/  SQLITE_AFF_BLOB ; 
 size_t SQLITE_LIMIT_COLUMN ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3AffinityType (char*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3ColumnPropertiesFromName (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,char*) ; 
 char* sqlite3DbMallocRaw (TYPE_2__*,size_t) ; 
 TYPE_6__* sqlite3DbRealloc (TYPE_2__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  sqlite3Dequote (char*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_5__*,char*,char*) ; 
 TYPE_9__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3RenameTokenMap (TYPE_5__*,void*,TYPE_3__*) ; 
 int sqlite3Strlen30 (char*) ; 
 scalar_t__ sqlite3_stricmp (char*,char*) ; 

void sqlite3AddColumn(Parse *pParse, Token *pName, Token *pType){
  Table *p;
  int i;
  char *z;
  char *zType;
  Column *pCol;
  sqlite3 *db = pParse->db;
  if( (p = pParse->pNewTable)==0 ) return;
  if( p->nCol+1>db->aLimit[SQLITE_LIMIT_COLUMN] ){
    sqlite3ErrorMsg(pParse, "too many columns on %s", p->zName);
    return;
  }
  z = sqlite3DbMallocRaw(db, pName->n + pType->n + 2);
  if( z==0 ) return;
  if( IN_RENAME_OBJECT ) sqlite3RenameTokenMap(pParse, (void*)z, pName);
  memcpy(z, pName->z, pName->n);
  z[pName->n] = 0;
  sqlite3Dequote(z);
  for(i=0; i<p->nCol; i++){
    if( sqlite3_stricmp(z, p->aCol[i].zName)==0 ){
      sqlite3ErrorMsg(pParse, "duplicate column name: %s", z);
      sqlite3DbFree(db, z);
      return;
    }
  }
  if( (p->nCol & 0x7)==0 ){
    Column *aNew;
    aNew = sqlite3DbRealloc(db,p->aCol,(p->nCol+8)*sizeof(p->aCol[0]));
    if( aNew==0 ){
      sqlite3DbFree(db, z);
      return;
    }
    p->aCol = aNew;
  }
  pCol = &p->aCol[p->nCol];
  memset(pCol, 0, sizeof(p->aCol[0]));
  pCol->zName = z;
  sqlite3ColumnPropertiesFromName(p, pCol);
 
  if( pType->n==0 ){
    /* If there is no type specified, columns have the default affinity
    ** 'BLOB' with a default size of 4 bytes. */
    pCol->affinity = SQLITE_AFF_BLOB;
    pCol->szEst = 1;
#ifdef SQLITE_ENABLE_SORTER_REFERENCES
    if( 4>=sqlite3GlobalConfig.szSorterRef ){
      pCol->colFlags |= COLFLAG_SORTERREF;
    }
#endif
  }else{
    zType = z + sqlite3Strlen30(z) + 1;
    memcpy(zType, pType->z, pType->n);
    zType[pType->n] = 0;
    sqlite3Dequote(zType);
    pCol->affinity = sqlite3AffinityType(zType, pCol);
    pCol->colFlags |= COLFLAG_HASTYPE;
  }
  p->nCol++;
  pParse->constraintName.n = 0;
}