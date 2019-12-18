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
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 

__attribute__((used)) static void ptrmap_coverage_report(const char *zDbName){
  int pgno;
  unsigned char *aHdr;
  unsigned char *a;
  int usable;
  int perPage;
  int i;

  /* Avoid the pathological case */
  if( g.mxPage<1 ){
    printf("empty database\n");
    return;
  }

  /* Make sure PTRMAPs are used in this database */
  aHdr = fileRead(0, 100);
  if( aHdr[55]==0 ){
    printf("database does not use PTRMAP pages\n");
    return;
  }
  usable = g.pagesize - aHdr[20];
  perPage = usable/5;
  sqlite3_free(aHdr);
  printf("%5d: root of sqlite_master\n", 1);
  for(pgno=2; pgno<=g.mxPage; pgno += perPage+1){
    printf("%5d: PTRMAP page covering %d..%d\n", pgno,
           pgno+1, pgno+perPage);
    a = fileRead((pgno-1)*g.pagesize, usable);
    for(i=0; i+5<=usable && pgno+1+i/5<=g.mxPage; i+=5){
      const char *zType = "???";
      unsigned int iFrom = decodeInt32(&a[i+1]);
      switch( a[i] ){
        case 1:  zType = "b-tree root page";        break;
        case 2:  zType = "freelist page";           break;
        case 3:  zType = "first page of overflow";  break;
        case 4:  zType = "later page of overflow";  break;
        case 5:  zType = "b-tree non-root page";    break;
      }
      printf("%5d: %s, parent=%u\n", pgno+1+i/5, zType, iFrom);
    }
    sqlite3_free(a);
  }
}