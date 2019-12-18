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
struct TYPE_4__ {unsigned int (* putdata ) (TYPE_1__*,void*,unsigned int) ;} ;
typedef  TYPE_1__ stbfile ;

/* Variables and functions */
 unsigned int stub1 (TYPE_1__*,void*,unsigned int) ; 

unsigned int stb_putdata(stbfile *f, void *buffer, unsigned int len)
{
   return f->putdata(f, buffer, len);
}