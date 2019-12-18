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
typedef  int /*<<< orphan*/  stb_uchar ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stb__out ; 
 int stb__outbytes ; 
 int /*<<< orphan*/  stb__outfile ; 
 int /*<<< orphan*/  stb_compress_inner (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  stb_p_fopen (char*,char*) ; 

int stb_compress_tofile(char *filename, char *input, unsigned int length)
{
   //int maxlen = length + 512 + (length >> 2); // total guess
   //char *buffer = (char *) malloc(maxlen);
   //int blen = stb_compress((stb_uchar*)buffer, (stb_uchar*)input, length);
   
   stb__out = NULL;
   stb__outfile = stb_p_fopen(filename, "wb");
   if (!stb__outfile) return 0;

   stb__outbytes = 0;

   if (!stb_compress_inner((stb_uchar*)input, length))
      return 0;

   fclose(stb__outfile);

   return stb__outbytes;
}