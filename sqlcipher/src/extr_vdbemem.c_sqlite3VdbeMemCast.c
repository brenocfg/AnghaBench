#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_10__ {int flags; TYPE_1__* db; } ;
struct TYPE_9__ {int /*<<< orphan*/  mallocFailed; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Blob ; 
 int MEM_Int ; 
 int MEM_Null ; 
 int MEM_Real ; 
 int MEM_Str ; 
 int MEM_TypeMask ; 
 int MEM_Zero ; 
 int /*<<< orphan*/  MemSetTypeFlag (TYPE_2__*,int) ; 
#define  SQLITE_AFF_BLOB 131 
#define  SQLITE_AFF_INTEGER 130 
#define  SQLITE_AFF_NUMERIC 129 
#define  SQLITE_AFF_REAL 128 
 int SQLITE_AFF_TEXT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ValueApplyAffinity (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIntegerify (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemNumerify (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRealify (TYPE_2__*) ; 

void sqlite3VdbeMemCast(Mem *pMem, u8 aff, u8 encoding){
  if( pMem->flags & MEM_Null ) return;
  switch( aff ){
    case SQLITE_AFF_BLOB: {   /* Really a cast to BLOB */
      if( (pMem->flags & MEM_Blob)==0 ){
        sqlite3ValueApplyAffinity(pMem, SQLITE_AFF_TEXT, encoding);
        assert( pMem->flags & MEM_Str || pMem->db->mallocFailed );
        if( pMem->flags & MEM_Str ) MemSetTypeFlag(pMem, MEM_Blob);
      }else{
        pMem->flags &= ~(MEM_TypeMask&~MEM_Blob);
      }
      break;
    }
    case SQLITE_AFF_NUMERIC: {
      sqlite3VdbeMemNumerify(pMem);
      break;
    }
    case SQLITE_AFF_INTEGER: {
      sqlite3VdbeMemIntegerify(pMem);
      break;
    }
    case SQLITE_AFF_REAL: {
      sqlite3VdbeMemRealify(pMem);
      break;
    }
    default: {
      assert( aff==SQLITE_AFF_TEXT );
      assert( MEM_Str==(MEM_Blob>>3) );
      pMem->flags |= (pMem->flags&MEM_Blob)>>3;
      sqlite3ValueApplyAffinity(pMem, SQLITE_AFF_TEXT, encoding);
      assert( pMem->flags & MEM_Str || pMem->db->mallocFailed );
      pMem->flags &= ~(MEM_Int|MEM_Real|MEM_Blob|MEM_Zero);
      break;
    }
  }
}