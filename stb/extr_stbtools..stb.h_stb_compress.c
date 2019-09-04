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
typedef  int /*<<< orphan*/  stb_uchar ;

/* Variables and functions */
 int /*<<< orphan*/ * stb__out ; 
 int /*<<< orphan*/ * stb__outfile ; 
 int /*<<< orphan*/  stb_compress_inner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

stb_uint stb_compress(stb_uchar *out, stb_uchar *input, stb_uint length)
{
   stb__out = out;
   stb__outfile = NULL;

   stb_compress_inner(input, length);

   return (stb_uint) (stb__out - out);
}