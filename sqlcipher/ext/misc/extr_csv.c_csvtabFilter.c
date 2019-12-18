#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pVtab; } ;
typedef  TYPE_2__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_7__ {scalar_t__ in; scalar_t__ zIn; size_t nIn; scalar_t__ iIn; } ;
struct TYPE_10__ {TYPE_1__ rdr; scalar_t__ iRowid; } ;
struct TYPE_9__ {scalar_t__ zData; scalar_t__ iStart; } ;
typedef  TYPE_3__ CsvTable ;
typedef  TYPE_4__ CsvCursor ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int csvtabNext (TYPE_2__*) ; 
 int /*<<< orphan*/  fseek (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csvtabFilter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  CsvCursor *pCur = (CsvCursor*)pVtabCursor;
  CsvTable *pTab = (CsvTable*)pVtabCursor->pVtab;
  pCur->iRowid = 0;
  if( pCur->rdr.in==0 ){
    assert( pCur->rdr.zIn==pTab->zData );
    assert( pTab->iStart>=0 );
    assert( (size_t)pTab->iStart<=pCur->rdr.nIn );
    pCur->rdr.iIn = pTab->iStart;
  }else{
    fseek(pCur->rdr.in, pTab->iStart, SEEK_SET);
    pCur->rdr.iIn = 0;
    pCur->rdr.nIn = 0;
  }
  return csvtabNext(pVtabCursor);
}