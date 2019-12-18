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
struct TYPE_2__ {int mxPage; int pagesize; } ;

/* Variables and functions */
 unsigned int decodeInt32 (unsigned char*) ; 
 unsigned char* fileRead (int,int) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  page_usage_cell (unsigned char,unsigned char*,int,int) ; 
 int /*<<< orphan*/  page_usage_msg (int,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 

__attribute__((used)) static void page_usage_btree(
  int pgno,             /* Page to describe */
  int parent,           /* Parent of this page.  0 for root pages */
  int idx,              /* Which child of the parent */
  const char *zName     /* Name of the table */
){
  unsigned char *a;
  const char *zType = "corrupt node";
  int nCell;
  int i;
  int hdr = pgno==1 ? 100 : 0;

  if( pgno<=0 || pgno>g.mxPage ) return;
  a = fileRead((pgno-1)*g.pagesize, g.pagesize);
  switch( a[hdr] ){
    case 2:  zType = "interior node of index";  break;
    case 5:  zType = "interior node of table";  break;
    case 10: zType = "leaf of index";           break;
    case 13: zType = "leaf of table";           break;
  }
  if( parent ){
    page_usage_msg(pgno, "%s [%s], child %d of page %d",
                   zType, zName, idx, parent);
  }else{
    page_usage_msg(pgno, "root %s [%s]", zType, zName);
  }
  nCell = a[hdr+3]*256 + a[hdr+4];
  if( a[hdr]==2 || a[hdr]==5 ){
    int cellstart = hdr+12;
    unsigned int child;
    for(i=0; i<nCell; i++){
      int ofst;

      ofst = cellstart + i*2;
      ofst = a[ofst]*256 + a[ofst+1];
      child = decodeInt32(a+ofst);
      page_usage_btree(child, pgno, i, zName);
    }
    child = decodeInt32(a+cellstart-4);
    page_usage_btree(child, pgno, i, zName);
  }
  if( a[hdr]==2 || a[hdr]==10 || a[hdr]==13 ){
    int cellstart = hdr + 8 + 4*(a[hdr]<=5);
    for(i=0; i<nCell; i++){
      int ofst;
      ofst = cellstart + i*2;
      ofst = a[ofst]*256 + a[ofst+1];
      page_usage_cell(a[hdr], a+ofst, pgno, i);
    }
  }
  sqlite3_free(a);
}