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
 int O_endpoint ; 
 int O_lever ; 
 int is_platform (short*) ; 

__attribute__((used)) static int allow_link(short *src, short *dest)
{
   if (is_platform(src))
      return dest[1] == 256+O_lever;
   if (src[1] == 256+O_endpoint)
      return is_platform(dest);
   return 0;
}