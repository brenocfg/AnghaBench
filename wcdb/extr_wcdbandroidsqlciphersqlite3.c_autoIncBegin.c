#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int tabFlags; int nCol; } ;
typedef  TYPE_3__ Table ;
struct TYPE_19__ {int mDbFlags; TYPE_2__* aDb; } ;
struct TYPE_18__ {int iDb; int regCtr; TYPE_3__* pTab; struct TYPE_18__* pNext; } ;
struct TYPE_17__ {int nMem; TYPE_5__* pAinc; TYPE_9__* db; int /*<<< orphan*/  rc; int /*<<< orphan*/  nErr; } ;
struct TYPE_15__ {TYPE_1__* pSchema; } ;
struct TYPE_14__ {TYPE_3__* pSeqTab; } ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ AutoincInfo ;

/* Variables and functions */
 int DBFLAG_Vacuum ; 
 int /*<<< orphan*/  HasRowid (TYPE_3__*) ; 
 scalar_t__ IsVirtual (TYPE_3__*) ; 
 int /*<<< orphan*/  SQLITE_CORRUPT_SEQUENCE ; 
 int TF_Autoincrement ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* sqlite3DbMallocRawNN (TYPE_9__*,int) ; 
 TYPE_4__* sqlite3ParseToplevel (TYPE_4__*) ; 

__attribute__((used)) static int autoIncBegin(
  Parse *pParse,      /* Parsing context */
  int iDb,            /* Index of the database holding pTab */
  Table *pTab         /* The table we are writing to */
){
  int memId = 0;      /* Register holding maximum rowid */
  assert( pParse->db->aDb[iDb].pSchema!=0 );
  if( (pTab->tabFlags & TF_Autoincrement)!=0
   && (pParse->db->mDbFlags & DBFLAG_Vacuum)==0
  ){
    Parse *pToplevel = sqlite3ParseToplevel(pParse);
    AutoincInfo *pInfo;
    Table *pSeqTab = pParse->db->aDb[iDb].pSchema->pSeqTab;

    /* Verify that the sqlite_sequence table exists and is an ordinary
    ** rowid table with exactly two columns.
    ** Ticket d8dc2b3a58cd5dc2918a1d4acb 2018-05-23 */
    if( pSeqTab==0
     || !HasRowid(pSeqTab)
     || IsVirtual(pSeqTab)
     || pSeqTab->nCol!=2
    ){
      pParse->nErr++;
      pParse->rc = SQLITE_CORRUPT_SEQUENCE;
      return 0;
    }

    pInfo = pToplevel->pAinc;
    while( pInfo && pInfo->pTab!=pTab ){ pInfo = pInfo->pNext; }
    if( pInfo==0 ){
      pInfo = sqlite3DbMallocRawNN(pParse->db, sizeof(*pInfo));
      if( pInfo==0 ) return 0;
      pInfo->pNext = pToplevel->pAinc;
      pToplevel->pAinc = pInfo;
      pInfo->pTab = pTab;
      pInfo->iDb = iDb;
      pToplevel->nMem++;                  /* Register to hold name of table */
      pInfo->regCtr = ++pToplevel->nMem;  /* Max rowid register */
      pToplevel->nMem +=2;       /* Rowid in sqlite_sequence + orig max val */
    }
    memId = pInfo->regCtr;
  }
  return memId;
}