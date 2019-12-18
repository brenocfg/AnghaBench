#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* count; int* state; } ;
struct TYPE_4__ {TYPE_1__ cx; } ;

/* Variables and functions */
 TYPE_2__ g ; 
 int /*<<< orphan*/  hash_step (unsigned char const*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 

__attribute__((used)) static void hash_finish(const char *zName){
  unsigned int i;
  unsigned char finalcount[8];
  unsigned char digest[20];
  static const char zEncode[] = "0123456789abcdef";
  char zOut[41];

  for (i = 0; i < 8; i++){
    finalcount[i] = (unsigned char)((g.cx.count[(i >= 4 ? 0 : 1)]
       >> ((3-(i & 3)) * 8) ) & 255); /* Endian independent */
  }
  hash_step((const unsigned char *)"\200", 1);
  while ((g.cx.count[0] & 504) != 448){
    hash_step((const unsigned char *)"\0", 1);
  }
  hash_step(finalcount, 8);  /* Should cause a SHA1Transform() */
  for (i = 0; i < 20; i++){
    digest[i] = (unsigned char)((g.cx.state[i>>2] >> ((3-(i & 3)) * 8) ) & 255);
  }
  for(i=0; i<20; i++){
    zOut[i*2] = zEncode[(digest[i]>>4)&0xf];
    zOut[i*2+1] = zEncode[digest[i] & 0xf];
  }
  zOut[i*2]= 0;
  printf("%s %s\n", zOut, zName);
}