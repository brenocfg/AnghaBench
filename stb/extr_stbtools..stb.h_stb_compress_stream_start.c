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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * stb__out ; 
 int /*<<< orphan*/ * stb__outfile ; 
 int /*<<< orphan*/  stb_compress_streaming_start () ; 

int stb_compress_stream_start(FILE *f)
{
   stb__out = NULL;
   stb__outfile = f;

   if (f == NULL)
      return 0;

   if (!stb_compress_streaming_start())
      return 0;

   return 1;
}