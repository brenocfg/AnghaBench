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
struct TYPE_2__ {unsigned int* s; } ;

/* Variables and functions */
 TYPE_1__ sqlite3Prng ; 

__attribute__((used)) static void fuzzRandomSeed(unsigned int iSeed){
  int i;
  for(i=0; i<256; i+=4){
    sqlite3Prng.s[i] ^= ((iSeed >> 24) & 0xFF);
    sqlite3Prng.s[i+1] ^= ((iSeed >> 16) & 0xFF);
    sqlite3Prng.s[i+2] ^= ((iSeed >>  8) & 0xFF);
    sqlite3Prng.s[i+3] ^= ((iSeed >>  0) & 0xFF);
  }
}