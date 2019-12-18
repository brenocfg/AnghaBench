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
struct TYPE_2__ {int iCursor; int iNext; char* aDelta; size_t a1; unsigned int a2; int nDelta; int /*<<< orphan*/  eOp; } ;
typedef  TYPE_1__ deltaparsevtab_cursor ;

/* Variables and functions */
 int /*<<< orphan*/  DELTAPARSE_OP_CHECKSUM ; 
 int /*<<< orphan*/  DELTAPARSE_OP_COPY ; 
 int /*<<< orphan*/  DELTAPARSE_OP_EOF ; 
 int /*<<< orphan*/  DELTAPARSE_OP_ERROR ; 
 int /*<<< orphan*/  DELTAPARSE_OP_INSERT ; 
 int SQLITE_OK ; 
 void* deltaGetInt (char const**,int*) ; 

__attribute__((used)) static int deltaparsevtabNext(sqlite3_vtab_cursor *cur){
  deltaparsevtab_cursor *pCur = (deltaparsevtab_cursor*)cur;
  const char *z;
  int i = 0;

  pCur->iCursor = pCur->iNext;
  z = pCur->aDelta + pCur->iCursor;
  pCur->a1 = deltaGetInt(&z, &i);
  switch( z[0] ){
    case '@': {
      z++;
      pCur->a2 = deltaGetInt(&z, &i);
      pCur->eOp = DELTAPARSE_OP_COPY;
      pCur->iNext = (int)(&z[1] - pCur->aDelta);
      break;
    }
    case ':': {
      z++;
      pCur->a2 = (unsigned int)(z - pCur->aDelta);
      pCur->eOp = DELTAPARSE_OP_INSERT;
      pCur->iNext = (int)(&z[pCur->a1] - pCur->aDelta);
      break;
    }
    case ';': {
      pCur->eOp = DELTAPARSE_OP_CHECKSUM;
      pCur->iNext = pCur->nDelta;
      break;
    }
    default: {
      if( pCur->iNext==pCur->nDelta ){
        pCur->eOp = DELTAPARSE_OP_EOF;
      }else{
        pCur->eOp = DELTAPARSE_OP_ERROR;
        pCur->iNext = pCur->nDelta;
      }
      break;
    }
  }
  return SQLITE_OK;
}