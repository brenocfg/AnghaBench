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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void printBytes(
  unsigned char *aData,      /* Content being decoded */
  unsigned char *aStart,     /* Start of content to be printed */
  int nByte                  /* Number of bytes to print */
){
  int j;
  printf(" %03x: ", (int)(aStart-aData));
  for(j=0; j<9; j++){
    if( j>=nByte ){
      printf("   ");
    }else{
      printf("%02x ", aStart[j]);
    }
  }
}