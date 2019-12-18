#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ stbfile ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  stb_arr_addn (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int stb__aputdata(stbfile *f, void *data, unsigned int len)
{
   memcpy(stb_arr_addn(f->buffer, (int) len), data, len);
   return len;
}