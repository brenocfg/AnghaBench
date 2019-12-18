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
typedef  scalar_t__ stb_uint ;
typedef  int /*<<< orphan*/  stb_uchar ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ stb__barrier ; 
 int /*<<< orphan*/ * stb__barrier2 ; 
 scalar_t__ stb__dout ; 

__attribute__((used)) static void stb__lit(stb_uchar *data, stb_uint length)
{
   assert (stb__dout + length <= stb__barrier);
   if (stb__dout + length > stb__barrier) { stb__dout += length; return; }
   if (data < stb__barrier2) { stb__dout = stb__barrier+1; return; }
   memcpy(stb__dout, data, length);
   stb__dout += length;
}