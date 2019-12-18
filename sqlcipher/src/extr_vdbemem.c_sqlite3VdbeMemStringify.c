#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_10__ {int /*<<< orphan*/  r; int /*<<< orphan*/  i; } ;
struct TYPE_11__ {int flags; scalar_t__ enc; int /*<<< orphan*/  z; int /*<<< orphan*/  n; TYPE_2__ u; TYPE_1__* db; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 int EIGHT_BYTE_ALIGNMENT (TYPE_3__*) ; 
 int MEM_Blob ; 
 int MEM_Int ; 
 int MEM_Real ; 
 int MEM_Str ; 
 int MEM_Term ; 
 int MEM_Zero ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Strlen30NN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeEncoding (TYPE_3__*,scalar_t__) ; 
 scalar_t__ sqlite3VdbeMemClearAndResize (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_3__*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int const,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int sqlite3VdbeMemStringify(Mem *pMem, u8 enc, u8 bForce){
  int fg = pMem->flags;
  const int nByte = 32;

  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
  assert( !(fg&MEM_Zero) );
  assert( !(fg&(MEM_Str|MEM_Blob)) );
  assert( fg&(MEM_Int|MEM_Real) );
  assert( !sqlite3VdbeMemIsRowSet(pMem) );
  assert( EIGHT_BYTE_ALIGNMENT(pMem) );


  if( sqlite3VdbeMemClearAndResize(pMem, nByte) ){
    pMem->enc = 0;
    return SQLITE_NOMEM_BKPT;
  }

  /* For a Real or Integer, use sqlite3_snprintf() to produce the UTF-8
  ** string representation of the value. Then, if the required encoding
  ** is UTF-16le or UTF-16be do a translation.
  ** 
  ** FIX ME: It would be better if sqlite3_snprintf() could do UTF-16.
  */
  if( fg & MEM_Int ){
    sqlite3_snprintf(nByte, pMem->z, "%lld", pMem->u.i);
  }else{
    assert( fg & MEM_Real );
    sqlite3_snprintf(nByte, pMem->z, "%!.15g", pMem->u.r);
  }
  assert( pMem->z!=0 );
  pMem->n = sqlite3Strlen30NN(pMem->z);
  pMem->enc = SQLITE_UTF8;
  pMem->flags |= MEM_Str|MEM_Term;
  if( bForce ) pMem->flags &= ~(MEM_Int|MEM_Real);
  sqlite3VdbeChangeEncoding(pMem, enc);
  return SQLITE_OK;
}