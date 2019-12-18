#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_8__ {scalar_t__ iType; } ;
typedef  int /*<<< orphan*/  DocListReader ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 scalar_t__ DL_POSITIONS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  docListAddDocid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  docListAddPos (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  docListDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  docListInit (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readDocid (int /*<<< orphan*/ *) ; 
 int readPosition (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  readerInit (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void docListDiscardEmpty(DocList *in) {
  DocListReader r;
  DocList out;

  /* TODO: It would be nice to implement this operation in place; that
   * could save a significant amount of memory in queries with long doclists. */
  assert( in->iType>=DL_POSITIONS );
  readerInit(&r, in);
  docListInit(&out, DL_POSITIONS, NULL, 0);

  while( !atEnd(&r) ){
    sqlite_int64 iDocid = readDocid(&r);
    int match = 0;
    int iPos, iColumn;
    while( (iPos = readPosition(&r, &iColumn)) != -1 ){
      if( !match ){
        docListAddDocid(&out, iDocid);
        match = 1;
      }
      docListAddPos(&out, iColumn, iPos);
    }
  }

  docListDestroy(in);
  *in = out;
}