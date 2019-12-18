#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  zName; TYPE_4__* pFKey; } ;
typedef  TYPE_2__ Table ;
struct TYPE_16__ {scalar_t__* aAction; struct TYPE_16__* pNextTo; int /*<<< orphan*/  zTo; struct TYPE_16__* pNextFrom; } ;
struct TYPE_15__ {TYPE_1__* db; } ;
struct TYPE_13__ {int flags; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ FKey ;

/* Variables and functions */
 scalar_t__ OE_None ; 
 int SQLITE_ForeignKeys ; 
 scalar_t__ fkChildIsModified (TYPE_2__*,TYPE_4__*,int*,int) ; 
 scalar_t__ fkParentIsModified (TYPE_2__*,TYPE_4__*,int*,int) ; 
 TYPE_4__* sqlite3FkReferences (TYPE_2__*) ; 
 scalar_t__ sqlite3_stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3FkRequired(
  Parse *pParse,                  /* Parse context */
  Table *pTab,                    /* Table being modified */
  int *aChange,                   /* Non-NULL for UPDATE operations */
  int chngRowid                   /* True for UPDATE that affects rowid */
){
  int eRet = 0;
  if( pParse->db->flags&SQLITE_ForeignKeys ){
    if( !aChange ){
      /* A DELETE operation. Foreign key processing is required if the 
      ** table in question is either the child or parent table for any 
      ** foreign key constraint.  */
      eRet = (sqlite3FkReferences(pTab) || pTab->pFKey);
    }else{
      /* This is an UPDATE. Foreign key processing is only required if the
      ** operation modifies one or more child or parent key columns. */
      FKey *p;

      /* Check if any child key columns are being modified. */
      for(p=pTab->pFKey; p; p=p->pNextFrom){
        if( 0==sqlite3_stricmp(pTab->zName, p->zTo) ) return 2;
        if( fkChildIsModified(pTab, p, aChange, chngRowid) ){
          eRet = 1;
        }
      }

      /* Check if any parent key columns are being modified. */
      for(p=sqlite3FkReferences(pTab); p; p=p->pNextTo){
        if( fkParentIsModified(pTab, p, aChange, chngRowid) ){
          if( p->aAction[1]!=OE_None ) return 2;
          eRet = 1;
        }
      }
    }
  }
  return eRet;
}