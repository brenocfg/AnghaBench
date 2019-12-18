#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_8__ {int /*<<< orphan*/  db; int /*<<< orphan*/  iNodeSize; int /*<<< orphan*/ * pWriteNode; } ;
struct TYPE_7__ {int /*<<< orphan*/  iNode; scalar_t__ isDirty; int /*<<< orphan*/  zData; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  TYPE_2__ Rtree ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  nodeHashInsert (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_last_insert_rowid (int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nodeWrite(Rtree *pRtree, RtreeNode *pNode){
  int rc = SQLITE_OK;
  if( pNode->isDirty ){
    sqlite3_stmt *p = pRtree->pWriteNode;
    if( pNode->iNode ){
      sqlite3_bind_int64(p, 1, pNode->iNode);
    }else{
      sqlite3_bind_null(p, 1);
    }
    sqlite3_bind_blob(p, 2, pNode->zData, pRtree->iNodeSize, SQLITE_STATIC);
    sqlite3_step(p);
    pNode->isDirty = 0;
    rc = sqlite3_reset(p);
    sqlite3_bind_null(p, 2);
    if( pNode->iNode==0 && rc==SQLITE_OK ){
      pNode->iNode = sqlite3_last_insert_rowid(pRtree->db);
      nodeHashInsert(pRtree, pNode);
    }
  }
  return rc;
}