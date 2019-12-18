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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 scalar_t__ get_int16 (int /*<<< orphan*/  const*) ; 
 int get_uint16 (int /*<<< orphan*/  const*) ; 

int32_t
jbig2_get_int32(const byte *bptr)
{
    return ((int32_t) get_int16(bptr) << 16) | get_uint16(bptr + 2);
}