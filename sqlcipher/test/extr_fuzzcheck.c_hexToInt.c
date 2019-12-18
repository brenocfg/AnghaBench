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

__attribute__((used)) static unsigned char hexToInt(unsigned int h){
#ifdef SQLITE_EBCDIC
  h += 9*(1&~(h>>4));   /* EBCDIC */
#else
  h += 9*(1&(h>>6));    /* ASCII */
#endif
  return h & 0xf;
}