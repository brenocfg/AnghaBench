#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int i64 ;

/* Variables and functions */
 int describeCell (unsigned char,unsigned char*,int,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int pagesize ; 
 int /*<<< orphan*/  print_decode_line (unsigned char*,int,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void decode_btree_page(
  unsigned char *a,   /* Content of the btree page to be decoded */
  int pgno,           /* Page number */
  int hdrSize,        /* Size of the page1-header in bytes */
  const char *zArgs   /* Flags to control formatting */
){
  const char *zType = "unknown";
  int nCell;
  int i, j;
  int iCellPtr;
  int showCellContent = 0;
  int showMap = 0;
  char *zMap = 0;
  switch( a[0] ){
    case 2:  zType = "index interior node";  break;
    case 5:  zType = "table interior node";  break;
    case 10: zType = "index leaf";           break;
    case 13: zType = "table leaf";           break;
  }
  while( zArgs[0] ){
    switch( zArgs[0] ){
      case 'c': showCellContent = 1;  break;
      case 'm': showMap = 1;          break;
    }
    zArgs++;
  }
  printf("Decode of btree page %d:\n", pgno);
  print_decode_line(a, 0, 1, 0, zType);
  print_decode_line(a, 1, 2, 0, "Offset to first freeblock");
  print_decode_line(a, 3, 2, 0, "Number of cells on this page");
  nCell = a[3]*256 + a[4];
  print_decode_line(a, 5, 2, 0, "Offset to cell content area");
  print_decode_line(a, 7, 1, 0, "Fragmented byte count");
  if( a[0]==2 || a[0]==5 ){
    print_decode_line(a, 8, 4, 0, "Right child");
    iCellPtr = 12;
  }else{
    iCellPtr = 8;
  }
  if( nCell>0 ){
    printf(" key: lx=left-child n=payload-size r=rowid\n");
  }
  if( showMap ){
    zMap = malloc(pagesize);
    memset(zMap, '.', pagesize);
    memset(zMap, '1', hdrSize);
    memset(&zMap[hdrSize], 'H', iCellPtr);
    memset(&zMap[hdrSize+iCellPtr], 'P', 2*nCell);
  }
  for(i=0; i<nCell; i++){
    int cofst = iCellPtr + i*2;
    char *zDesc;
    i64 n;

    cofst = a[cofst]*256 + a[cofst+1];
    n = describeCell(a[0], &a[cofst-hdrSize], showCellContent, &zDesc);
    if( showMap ){
      char zBuf[30];
      memset(&zMap[cofst], '*', (size_t)n);
      zMap[cofst] = '[';
      zMap[cofst+n-1] = ']';
      sprintf(zBuf, "%d", i);
      j = (int)strlen(zBuf);
      if( j<=n-2 ) memcpy(&zMap[cofst+1], zBuf, j);
    }
    printf(" %03x: cell[%d] %s\n", cofst, i, zDesc);
  }
  if( showMap ){
    for(i=0; i<pagesize; i+=64){
      printf(" %03x: %.64s\n", i, &zMap[i]);
    }
    free(zMap);
  }  
}