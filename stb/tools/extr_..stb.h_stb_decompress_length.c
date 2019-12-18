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
typedef  int stb_uint ;
typedef  int stb_uchar ;

/* Variables and functions */

stb_uint stb_decompress_length(stb_uchar *input)
{
   return (input[8] << 24) + (input[9] << 16) + (input[10] << 8) + input[11];
}