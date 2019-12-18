#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int r1; int r2; TYPE_2__* pKeyInfo; TYPE_1__* aMem; } ;
typedef  TYPE_3__ UnpackedRecord ;
struct TYPE_6__ {int nAllField; scalar_t__* aColl; scalar_t__* aSortOrder; } ;
struct TYPE_5__ {int flags; } ;
typedef  int /*<<< orphan*/  RecordCompare ;

/* Variables and functions */
 int MEM_Blob ; 
 int MEM_Int ; 
 int MEM_Null ; 
 int MEM_Real ; 
 int MEM_Str ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeRecordCompare ; 
 int /*<<< orphan*/  testcase (int) ; 
 int /*<<< orphan*/  vdbeRecordCompareInt ; 
 int /*<<< orphan*/  vdbeRecordCompareString ; 

RecordCompare sqlite3VdbeFindCompare(UnpackedRecord *p){
  /* varintRecordCompareInt() and varintRecordCompareString() both assume
  ** that the size-of-header varint that occurs at the start of each record
  ** fits in a single byte (i.e. is 127 or less). varintRecordCompareInt()
  ** also assumes that it is safe to overread a buffer by at least the 
  ** maximum possible legal header size plus 8 bytes. Because there is
  ** guaranteed to be at least 74 (but not 136) bytes of padding following each
  ** buffer passed to varintRecordCompareInt() this makes it convenient to
  ** limit the size of the header to 64 bytes in cases where the first field
  ** is an integer.
  **
  ** The easiest way to enforce this limit is to consider only records with
  ** 13 fields or less. If the first field is an integer, the maximum legal
  ** header size is (12*5 + 1 + 1) bytes.  */
  if( p->pKeyInfo->nAllField<=13 ){
    int flags = p->aMem[0].flags;
    if( p->pKeyInfo->aSortOrder[0] ){
      p->r1 = 1;
      p->r2 = -1;
    }else{
      p->r1 = -1;
      p->r2 = 1;
    }
    if( (flags & MEM_Int) ){
      return vdbeRecordCompareInt;
    }
    testcase( flags & MEM_Real );
    testcase( flags & MEM_Null );
    testcase( flags & MEM_Blob );
    if( (flags & (MEM_Real|MEM_Null|MEM_Blob))==0 && p->pKeyInfo->aColl[0]==0 ){
      assert( flags & MEM_Str );
      return vdbeRecordCompareString;
    }
  }

  return sqlite3VdbeRecordCompare;
}