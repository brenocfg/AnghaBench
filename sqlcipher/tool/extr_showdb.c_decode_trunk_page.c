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
struct TYPE_2__ {int pagesize; } ;

/* Variables and functions */
 unsigned int decodeInt32 (unsigned char*) ; 
 unsigned char* fileRead (int,int) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  print_decode_line (unsigned char*,int,int,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 

__attribute__((used)) static void decode_trunk_page(
  int pgno,             /* The page number */
  int detail,           /* Show leaf pages if true */
  int recursive         /* Follow the trunk change if true */
){
  int n, i;
  unsigned char *a;
  while( pgno>0 ){
    a = fileRead((pgno-1)*g.pagesize, g.pagesize);
    printf("Decode of freelist trunk page %d:\n", pgno);
    print_decode_line(a, 0, 4, "Next freelist trunk page");
    print_decode_line(a, 4, 4, "Number of entries on this page");
    if( detail ){
      n = (int)decodeInt32(&a[4]);
      for(i=0; i<n; i++){
        unsigned int x = decodeInt32(&a[8+4*i]);
        char zIdx[10];
        sprintf(zIdx, "[%d]", i);
        printf("  %5s %7u", zIdx, x);
        if( i%5==4 ) printf("\n");
      }
      if( i%5!=0 ) printf("\n");
    }
    if( !recursive ){
      pgno = 0;
    }else{
      pgno = (int)decodeInt32(&a[0]);
    }
    sqlite3_free(a);
  }
}