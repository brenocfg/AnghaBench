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
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/ * hexvals ; 

VOID  htoa (unsigned int val, char *buf)
{
   int i;
   buf += 7;

   for (i=0;i<8;i++)
       {
            *buf-- = hexvals[val & 0x0000000F];
            val = val >> 4;
       }
}