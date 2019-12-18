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
typedef  int /*<<< orphan*/  stb_uint ;

/* Variables and functions */
 int /*<<< orphan*/  stb_crc32_block (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

stb_uint stb_crc32(unsigned char *buffer, stb_uint len)
{
   return stb_crc32_block(0, buffer, len);
}