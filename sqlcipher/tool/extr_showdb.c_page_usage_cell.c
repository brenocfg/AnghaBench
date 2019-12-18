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
typedef  int sqlite3_int64 ;
typedef  scalar_t__ i64 ;
struct TYPE_2__ {scalar_t__ pagesize; int /*<<< orphan*/  mxPage; } ;

/* Variables and functions */
 int decodeInt32 (unsigned char*) ; 
 int decodeVarint (unsigned char*,scalar_t__*) ; 
 unsigned char* fileRead (int,int) ; 
 TYPE_1__ g ; 
 scalar_t__ localPayload (scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  page_usage_msg (int,char*,int,int,int) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 

__attribute__((used)) static void page_usage_cell(
  unsigned char cType,    /* Page type */
  unsigned char *a,       /* Cell content */
  int pgno,               /* page containing the cell */
  int cellno              /* Index of the cell on the page */
){
  int i;
  int n = 0;
  i64 nPayload;
  i64 rowid;
  i64 nLocal;
  i = 0;
  if( cType<=5 ){
    a += 4;
    n += 4;
  }
  if( cType!=5 ){
    i = decodeVarint(a, &nPayload);
    a += i;
    n += i;
    nLocal = localPayload(nPayload, cType);
  }else{
    nPayload = nLocal = 0;
  }
  if( cType==5 || cType==13 ){
    i = decodeVarint(a, &rowid);
    a += i;
    n += i;
  }
  if( nLocal<nPayload ){
    int ovfl = decodeInt32(a+nLocal);
    int cnt = 0;
    while( ovfl && (cnt++)<g.mxPage ){
      page_usage_msg(ovfl, "overflow %d from cell %d of page %d",
                     cnt, cellno, pgno);
      a = fileRead((ovfl-1)*(sqlite3_int64)g.pagesize, 4);
      ovfl = decodeInt32(a);
      sqlite3_free(a);
    }
  }
}