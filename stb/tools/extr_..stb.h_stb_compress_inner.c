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
typedef  int /*<<< orphan*/  stb_uchar ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  outliterals (int /*<<< orphan*/ *,int) ; 
 int stb__hashsize ; 
 int stb__running_adler ; 
 int stb__window ; 
 int stb_compress_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  stb_out (int) ; 
 int /*<<< orphan*/  stb_out2 (int) ; 
 int /*<<< orphan*/  stb_out4 (int) ; 

__attribute__((used)) static int stb_compress_inner(stb_uchar *input, stb_uint length)
{
   int literals = 0;
   stb_uint len,i;

   stb_uchar **chash;
   chash = (stb_uchar**) malloc(stb__hashsize * sizeof(stb_uchar*));
   if (chash == NULL) return 0; // failure
   for (i=0; i < stb__hashsize; ++i)
      chash[i] = NULL;

   // stream signature
   stb_out(0x57); stb_out(0xbc);
   stb_out2(0);

   stb_out4(0);       // 64-bit length requires 32-bit leading 0
   stb_out4(length);
   stb_out4(stb__window);

   stb__running_adler = 1;

   len = stb_compress_chunk(input, input, input+length, length, &literals, chash, stb__hashsize-1);
   assert(len == length);

   outliterals(input+length - literals, literals);

   free(chash);

   stb_out2(0x05fa); // end opcode

   stb_out4(stb__running_adler);

   return 1; // success
}