#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ xCmp; } ;
struct TYPE_14__ {scalar_t__ i; scalar_t__ r; } ;
struct TYPE_16__ {int flags; scalar_t__ enc; TYPE_2__* db; TYPE_1__ u; } ;
struct TYPE_15__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ Mem ;
typedef  TYPE_4__ CollSeq ;

/* Variables and functions */
 int MEM_Int ; 
 int MEM_Null ; 
 int MEM_Real ; 
 int MEM_Str ; 
 scalar_t__ SQLITE_UTF16BE ; 
 scalar_t__ SQLITE_UTF16LE ; 
 scalar_t__ SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3BlobCompare (TYPE_3__ const*,TYPE_3__ const*) ; 
 int sqlite3IntFloatCompare (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_3__ const*) ; 
 int vdbeCompareMemString (TYPE_3__ const*,TYPE_3__ const*,TYPE_4__ const*,int /*<<< orphan*/ ) ; 

int sqlite3MemCompare(const Mem *pMem1, const Mem *pMem2, const CollSeq *pColl){
  int f1, f2;
  int combined_flags;

  f1 = pMem1->flags;
  f2 = pMem2->flags;
  combined_flags = f1|f2;
  assert( !sqlite3VdbeMemIsRowSet(pMem1) && !sqlite3VdbeMemIsRowSet(pMem2) );
 
  /* If one value is NULL, it is less than the other. If both values
  ** are NULL, return 0.
  */
  if( combined_flags&MEM_Null ){
    return (f2&MEM_Null) - (f1&MEM_Null);
  }

  /* At least one of the two values is a number
  */
  if( combined_flags&(MEM_Int|MEM_Real) ){
    if( (f1 & f2 & MEM_Int)!=0 ){
      if( pMem1->u.i < pMem2->u.i ) return -1;
      if( pMem1->u.i > pMem2->u.i ) return +1;
      return 0;
    }
    if( (f1 & f2 & MEM_Real)!=0 ){
      if( pMem1->u.r < pMem2->u.r ) return -1;
      if( pMem1->u.r > pMem2->u.r ) return +1;
      return 0;
    }
    if( (f1&MEM_Int)!=0 ){
      if( (f2&MEM_Real)!=0 ){
        return sqlite3IntFloatCompare(pMem1->u.i, pMem2->u.r);
      }else{
        return -1;
      }
    }
    if( (f1&MEM_Real)!=0 ){
      if( (f2&MEM_Int)!=0 ){
        return -sqlite3IntFloatCompare(pMem2->u.i, pMem1->u.r);
      }else{
        return -1;
      }
    }
    return +1;
  }

  /* If one value is a string and the other is a blob, the string is less.
  ** If both are strings, compare using the collating functions.
  */
  if( combined_flags&MEM_Str ){
    if( (f1 & MEM_Str)==0 ){
      return 1;
    }
    if( (f2 & MEM_Str)==0 ){
      return -1;
    }

    assert( pMem1->enc==pMem2->enc || pMem1->db->mallocFailed );
    assert( pMem1->enc==SQLITE_UTF8 || 
            pMem1->enc==SQLITE_UTF16LE || pMem1->enc==SQLITE_UTF16BE );

    /* The collation sequence must be defined at this point, even if
    ** the user deletes the collation sequence after the vdbe program is
    ** compiled (this was not always the case).
    */
    assert( !pColl || pColl->xCmp );

    if( pColl ){
      return vdbeCompareMemString(pMem1, pMem2, pColl, 0);
    }
    /* If a NULL pointer was passed as the collate function, fall through
    ** to the blob case and use memcmp().  */
  }
 
  /* Both values must be blobs.  Compare using memcmp().  */
  return sqlite3BlobCompare(pMem1, pMem2);
}