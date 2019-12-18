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
typedef  int u8 ;
struct TYPE_8__ {int flags; int enc; void const* z; TYPE_1__* db; } ;
typedef  TYPE_2__ sqlite3_value ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int MEM_Null ; 
 int MEM_Str ; 
 int MEM_Term ; 
 int SQLITE_UTF16_ALIGNED ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3VdbeMemConsistentDualRep (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_2__*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 void const* valueToText (TYPE_2__*,int) ; 

const void *sqlite3ValueText(sqlite3_value* pVal, u8 enc){
  if( !pVal ) return 0;
  assert( pVal->db==0 || sqlite3_mutex_held(pVal->db->mutex) );
  assert( (enc&3)==(enc&~SQLITE_UTF16_ALIGNED) );
  assert( !sqlite3VdbeMemIsRowSet(pVal) );
  if( (pVal->flags&(MEM_Str|MEM_Term))==(MEM_Str|MEM_Term) && pVal->enc==enc ){
    assert( sqlite3VdbeMemConsistentDualRep(pVal) );
    return pVal->z;
  }
  if( pVal->flags&MEM_Null ){
    return 0;
  }
  return valueToText(pVal, enc);
}