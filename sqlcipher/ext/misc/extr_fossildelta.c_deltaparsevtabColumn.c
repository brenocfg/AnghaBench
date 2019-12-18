#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {size_t eOp; scalar_t__ nDelta; scalar_t__ aDelta; scalar_t__ a1; scalar_t__ a2; } ;
typedef  TYPE_1__ deltaparsevtab_cursor ;

/* Variables and functions */
#define  DELTAPARSEVTAB_A1 131 
#define  DELTAPARSEVTAB_A2 130 
#define  DELTAPARSEVTAB_DELTA 129 
#define  DELTAPARSEVTAB_OP 128 
 size_t DELTAPARSE_OP_COPY ; 
 size_t DELTAPARSE_OP_INSERT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/ * azOp ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int deltaparsevtabColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  deltaparsevtab_cursor *pCur = (deltaparsevtab_cursor*)cur;
  switch( i ){
    case DELTAPARSEVTAB_OP: {
      sqlite3_result_text(ctx, azOp[pCur->eOp], -1, SQLITE_STATIC);
      break;
    }
    case DELTAPARSEVTAB_A1: {
      sqlite3_result_int(ctx, pCur->a1);
      break;
    }
    case DELTAPARSEVTAB_A2: {
      if( pCur->eOp==DELTAPARSE_OP_COPY ){
        sqlite3_result_int(ctx, pCur->a2);
      }else if( pCur->eOp==DELTAPARSE_OP_INSERT ){
        sqlite3_result_blob(ctx, pCur->aDelta+pCur->a2, pCur->a1,
                            SQLITE_TRANSIENT);
      }
      break;
    }
    case DELTAPARSEVTAB_DELTA: {
      sqlite3_result_blob(ctx, pCur->aDelta, pCur->nDelta, SQLITE_TRANSIENT);
      break;
    }
  }
  return SQLITE_OK;
}