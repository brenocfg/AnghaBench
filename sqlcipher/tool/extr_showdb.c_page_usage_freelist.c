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
 int decodeInt32 (unsigned char*) ; 
 unsigned char* fileRead (int,int) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  page_usage_msg (int,char*,int,int) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 

__attribute__((used)) static void page_usage_freelist(int pgno){
  unsigned char *a;
  int cnt = 0;
  int i;
  int n;
  int iNext;
  int parent = 1;

  while( pgno>0 && pgno<=g.mxPage && (cnt++)<g.mxPage ){
    page_usage_msg(pgno, "freelist trunk #%d child of %d", cnt, parent);
    a = fileRead((pgno-1)*g.pagesize, g.pagesize);
    iNext = decodeInt32(a);
    n = decodeInt32(a+4);
    for(i=0; i<n; i++){
      int child = decodeInt32(a + (i*4+8));
      page_usage_msg(child, "freelist leaf, child %d of trunk page %d",
                     i, pgno);
    }
    sqlite3_free(a);
    parent = pgno;
    pgno = iNext;
  }
}