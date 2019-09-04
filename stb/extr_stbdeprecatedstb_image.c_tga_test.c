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
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int get16 (int /*<<< orphan*/ *) ; 
 int get8 (int /*<<< orphan*/ *) ; 
 int get8u (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tga_test(stbi *s)
{
   int sz;
   get8u(s);      //   discard Offset
   sz = get8u(s);   //   color type
   if ( sz > 1 ) return 0;   //   only RGB or indexed allowed
   sz = get8u(s);   //   image type
   if ( (sz != 1) && (sz != 2) && (sz != 3) && (sz != 9) && (sz != 10) && (sz != 11) ) return 0;   //   only RGB or grey allowed, +/- RLE
   get16(s);      //   discard palette start
   get16(s);      //   discard palette length
   get8(s);         //   discard bits per palette color entry
   get16(s);      //   discard x origin
   get16(s);      //   discard y origin
   if ( get16(s) < 1 ) return 0;      //   test width
   if ( get16(s) < 1 ) return 0;      //   test height
   sz = get8(s);   //   bits per pixel
   if ( (sz != 8) && (sz != 16) && (sz != 24) && (sz != 32) ) return 0;   //   only RGB or RGBA or grey allowed
   return 1;      //   seems to have passed everything
}