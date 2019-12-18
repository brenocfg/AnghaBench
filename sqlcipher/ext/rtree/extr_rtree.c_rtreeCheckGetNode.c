#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_6__ {scalar_t__ rc; scalar_t__ pGetNode; int /*<<< orphan*/  zTab; int /*<<< orphan*/  zDb; } ;
typedef  TYPE_1__ RtreeCheck ;

/* Variables and functions */
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  rtreeCheckAppendMsg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtreeCheckPrepare (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtreeCheckReset (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_blob (scalar_t__,int /*<<< orphan*/ ) ; 
 int sqlite3_column_bytes (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_malloc64 (int) ; 
 scalar_t__ sqlite3_step (scalar_t__) ; 

__attribute__((used)) static u8 *rtreeCheckGetNode(RtreeCheck *pCheck, i64 iNode, int *pnNode){
  u8 *pRet = 0;                   /* Return value */

  if( pCheck->rc==SQLITE_OK && pCheck->pGetNode==0 ){
    pCheck->pGetNode = rtreeCheckPrepare(pCheck,
        "SELECT data FROM %Q.'%q_node' WHERE nodeno=?", 
        pCheck->zDb, pCheck->zTab
    );
  }

  if( pCheck->rc==SQLITE_OK ){
    sqlite3_bind_int64(pCheck->pGetNode, 1, iNode);
    if( sqlite3_step(pCheck->pGetNode)==SQLITE_ROW ){
      int nNode = sqlite3_column_bytes(pCheck->pGetNode, 0);
      const u8 *pNode = (const u8*)sqlite3_column_blob(pCheck->pGetNode, 0);
      pRet = sqlite3_malloc64(nNode);
      if( pRet==0 ){
        pCheck->rc = SQLITE_NOMEM;
      }else{
        memcpy(pRet, pNode, nNode);
        *pnNode = nNode;
      }
    }
    rtreeCheckReset(pCheck, pCheck->pGetNode);
    if( pCheck->rc==SQLITE_OK && pRet==0 ){
      rtreeCheckAppendMsg(pCheck, "Node %lld missing from database", iNode);
    }
  }

  return pRet;
}