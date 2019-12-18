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
struct TYPE_2__ {size_t i; unsigned char* s; unsigned char j; } ;

/* Variables and functions */
 TYPE_1__ sqlite3Prng ; 

__attribute__((used)) static unsigned char randomByte(void){
  unsigned char t;
  sqlite3Prng.i++;
  t = sqlite3Prng.s[sqlite3Prng.i];
  sqlite3Prng.j += t;
  sqlite3Prng.s[sqlite3Prng.i] = sqlite3Prng.s[sqlite3Prng.j];
  sqlite3Prng.s[sqlite3Prng.j] = t;
  t += sqlite3Prng.s[sqlite3Prng.i];
  return sqlite3Prng.s[t];
}