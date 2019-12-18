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
struct TYPE_2__ {int perLine; } ;

/* Variables and functions */
 scalar_t__ ISPRINT (unsigned char) ; 
 unsigned char* fileRead (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char const*,...) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static unsigned char *print_byte_range(
  int ofst,          /* First byte in the range of bytes to print */
  int nByte,         /* Number of bytes to print */
  int printOfst      /* Add this amount to the index on the left column */
){
  unsigned char *aData;
  int i, j;
  const char *zOfstFmt;

  if( ((printOfst+nByte)&~0xfff)==0 ){
    zOfstFmt = " %03x: ";
  }else if( ((printOfst+nByte)&~0xffff)==0 ){
    zOfstFmt = " %04x: ";
  }else if( ((printOfst+nByte)&~0xfffff)==0 ){
    zOfstFmt = " %05x: ";
  }else if( ((printOfst+nByte)&~0xffffff)==0 ){
    zOfstFmt = " %06x: ";
  }else{
    zOfstFmt = " %08x: ";
  }

  aData = fileRead(ofst, nByte);
  for(i=0; i<nByte; i += g.perLine){
    fprintf(stdout, zOfstFmt, i+printOfst);
    for(j=0; j<g.perLine; j++){
      if( i+j>nByte ){
        fprintf(stdout, "   ");
      }else{
        fprintf(stdout,"%02x ", aData[i+j]);
      }
    }
    for(j=0; j<g.perLine; j++){
      if( i+j>nByte ){
        fprintf(stdout, " ");
      }else{
        fprintf(stdout,"%c", ISPRINT(aData[i+j]) ? aData[i+j] : '.');
      }
    }
    fprintf(stdout,"\n");
  }
  return aData;
}