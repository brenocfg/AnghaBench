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

int sqlite3Fts5UnicodeIsdiacritic(int c){
  unsigned int mask0 = 0x08029FDF;
  unsigned int mask1 = 0x000361F8;
  if( c<768 || c>817 ) return 0;
  return (c < 768+32) ?
      (mask0 & ((unsigned int)1 << (c-768))) :
      (mask1 & ((unsigned int)1 << (c-768-32)));
}