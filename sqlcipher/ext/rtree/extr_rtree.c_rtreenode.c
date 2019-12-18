#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_str ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_12__ {double iRowid; TYPE_1__* aCoord; } ;
struct TYPE_11__ {int nDim; int nDim2; int nBytesPerCell; int* zData; } ;
struct TYPE_10__ {double i; scalar_t__ f; } ;
typedef  TYPE_2__ RtreeNode ;
typedef  TYPE_3__ RtreeCell ;
typedef  TYPE_2__ Rtree ;

/* Variables and functions */
 int NCELL (TYPE_2__*) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nodeGetCell (TYPE_2__*,TYPE_2__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_str_append (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_str_appendf (int /*<<< orphan*/ *,char*,double) ; 
 int sqlite3_str_errcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_str_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_str_new (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtreenode(sqlite3_context *ctx, int nArg, sqlite3_value **apArg){
  RtreeNode node;
  Rtree tree;
  int ii;
  int nData;
  int errCode;
  sqlite3_str *pOut;

  UNUSED_PARAMETER(nArg);
  memset(&node, 0, sizeof(RtreeNode));
  memset(&tree, 0, sizeof(Rtree));
  tree.nDim = (u8)sqlite3_value_int(apArg[0]);
  if( tree.nDim<1 || tree.nDim>5 ) return;
  tree.nDim2 = tree.nDim*2;
  tree.nBytesPerCell = 8 + 8 * tree.nDim;
  node.zData = (u8 *)sqlite3_value_blob(apArg[1]);
  nData = sqlite3_value_bytes(apArg[1]);
  if( nData<4 ) return;
  if( nData<NCELL(&node)*tree.nBytesPerCell ) return;

  pOut = sqlite3_str_new(0);
  for(ii=0; ii<NCELL(&node); ii++){
    RtreeCell cell;
    int jj;

    nodeGetCell(&tree, &node, ii, &cell);
    if( ii>0 ) sqlite3_str_append(pOut, " ", 1);
    sqlite3_str_appendf(pOut, "{%lld", cell.iRowid);
    for(jj=0; jj<tree.nDim2; jj++){
#ifndef SQLITE_RTREE_INT_ONLY
      sqlite3_str_appendf(pOut, " %g", (double)cell.aCoord[jj].f);
#else
      sqlite3_str_appendf(pOut, " %d", cell.aCoord[jj].i);
#endif
    }
    sqlite3_str_append(pOut, "}", 1);
  }
  errCode = sqlite3_str_errcode(pOut);
  sqlite3_result_text(ctx, sqlite3_str_finish(pOut), -1, sqlite3_free);
  sqlite3_result_error_code(ctx, errCode);
}