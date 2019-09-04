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

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ stb__outfile ; 
 int /*<<< orphan*/  stb_compress_streaming_end () ; 

void stb_compress_stream_end(int close)
{
   stb_compress_streaming_end();
   if (close && stb__outfile) {
      fclose(stb__outfile);
   }
}