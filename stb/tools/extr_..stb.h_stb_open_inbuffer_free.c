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
struct TYPE_4__ {int various; } ;
typedef  TYPE_1__ stbfile ;

/* Variables and functions */
 TYPE_1__* stb_open_inbuffer (void*,unsigned int) ; 

stbfile *stb_open_inbuffer_free(void *buffer, unsigned int len)
{
   stbfile *z = stb_open_inbuffer(buffer, len);
   if (z)
      z->various = 1; // free
   return z;
}