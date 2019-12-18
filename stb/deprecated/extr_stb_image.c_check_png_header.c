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
typedef  int stbi__uint8 ;
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int e (char*,char*) ; 
 int get8u (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_png_header(stbi *s)
{
   static stbi__uint8 png_sig[8] = { 137,80,78,71,13,10,26,10 };
   int i;
   for (i=0; i < 8; ++i)
      if (get8u(s) != png_sig[i]) return e("bad png sig","Not a PNG");
   return 1;
}