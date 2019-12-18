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
typedef  int u64 ;
typedef  int i64 ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int hexValue (char) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int putVarint (unsigned char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int toHex (unsigned char) ; 

int main(int argc, char **argv){
  int i;
  u64 x;
  u64 uX = 0;
  i64 iX;
  int n;
  unsigned char zHex[20];

  if( argc==1 ){
    fprintf(stderr, 
         "Usage:\n"
         "  %s HH HH HH ...   Convert varint to decimal\n"
         "  %s DDDDD          Convert decimal to varint\n"
         "                    Add '+' or '-' before DDDDD to disambiguate.\n",
         argv[0], argv[0]);
    exit(1);
  }
  if( argc>2 
   || (strlen(argv[1])==2 && hexValue(argv[1][0])>=0 && hexValue(argv[1][1])>=0)
  ){
    /* Hex to decimal */
    for(i=1; i<argc && i<9; i++){
      if( strlen(argv[i])!=2 ){
        fprintf(stderr, "Not a hex byte: %s\n", argv[i]);
        exit(1);
      }
      x = (hexValue(argv[i][0])<<4) + hexValue(argv[i][1]);
      uX = (uX<<7) + (x&0x7f);
      if( (x&0x80)==0 ) break;
    }
    if( i==9 && i<argc ){
      if( strlen(argv[i])!=2 ){
        fprintf(stderr, "Not a hex byte: %s\n", argv[i]);
        exit(1);
      }
      x = (hexValue(argv[i][0])<<4) + hexValue(argv[i][1]);
      uX = (uX<<8) + x;
    }
    i++;
    if( i<argc ){
      fprintf(stderr, "Extra arguments: %s...\n", argv[i]);
      exit(1);
    }
  }else{
    char *z = argv[1];
    int sign = 1;
    if( z[0]=='+' ) z++;
    else if( z[0]=='-' ){ z++; sign = -1; }
    uX = 0;
    while( z[0] ){
      if( z[0]<'0' || z[0]>'9' ){
        fprintf(stderr, "Not a decimal number: %s", argv[1]);
        exit(1);
      }
      uX = uX*10 + z[0] - '0';
      z++;
    }
    if( sign<0 ){
      memcpy(&iX, &uX, 8);
      iX = -iX;
      memcpy(&uX, &iX, 8);
    }
  }
  n = putVarint(zHex, uX);
  printf("%lld =", (i64)uX);
  for(i=0; i<n; i++){
    printf(" %c%c", toHex(zHex[i]>>4), toHex(zHex[i]&0x0f));
  }
  printf("\n");
  return 0;
}