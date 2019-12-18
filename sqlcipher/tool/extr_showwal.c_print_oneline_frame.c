#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int s0; unsigned int s1; } ;
typedef  TYPE_1__ Cksum ;

/* Variables and functions */
 int /*<<< orphan*/  extendCksum (TYPE_1__*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* getContent (int,int) ; 
 int getInt32 (unsigned char*) ; 
 int pagesize ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void print_oneline_frame(int iFrame, Cksum *pCksum){
  int iStart;
  unsigned char *aData;
  unsigned int s0, s1;
  iStart = 32 + (iFrame-1)*(pagesize+24);
  aData = getContent(iStart, 24);
  extendCksum(pCksum, aData, 8, 0);
  extendCksum(pCksum, getContent(iStart+24, pagesize), pagesize, 0);
  s0 = getInt32(aData+16);
  s1 = getInt32(aData+20);
  fprintf(stdout, "Frame %4d: %6d %6d 0x%08x,%08x 0x%08x,%08x %s\n",
          iFrame, 
          getInt32(aData),
          getInt32(aData+4),
          getInt32(aData+8),
          getInt32(aData+12),
          s0,
          s1,
          (s0==pCksum->s0 && s1==pCksum->s1) ? "" : "cksum-fail"
  );

  /* Reset the checksum so that a single frame checksum failure will not
  ** cause all subsequent frames to also show a failure. */
  pCksum->s0 = s0;
  pCksum->s1 = s1;
  free(aData);
}