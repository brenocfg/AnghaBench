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
struct TYPE_4__ {int len; int dx; int y; } ;
typedef  TYPE_1__ segment ;

/* Variables and functions */
 scalar_t__ printf (char*,...) ; 
 int stb_arr_len (TYPE_1__*) ; 

void print_segments(segment *s)
{
   int i, hpos;
   printf("   ");
   hpos = 4;
   for (i=0; i < stb_arr_len(s); ++i) {
      // repack for portability
      unsigned char seg = s[i].len + s[i].dx*8 + s[i].y*16;
      hpos += printf("%d,", seg);
      if (hpos > 72 && i+1 < stb_arr_len(s)) {
         hpos = 4;
         printf("\n    ");
      }
   }
   printf("\n");
}