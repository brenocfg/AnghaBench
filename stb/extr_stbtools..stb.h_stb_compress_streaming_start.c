#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int stb_uint ;
typedef  int /*<<< orphan*/  stb_uchar ;
struct TYPE_2__ {int size; int hashmask; int window; int fsize; int length_id; scalar_t__ total_bytes; scalar_t__ pending_literals; scalar_t__ start; scalar_t__ valid; int /*<<< orphan*/ ** chash; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int stb__hashsize ; 
 int stb__running_adler ; 
 int stb__window ; 
 int /*<<< orphan*/  stb_out (int) ; 
 int /*<<< orphan*/  stb_out2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_out4 (int) ; 
 scalar_t__ stb_out_backpatch_id () ; 
 TYPE_1__ xtb ; 

__attribute__((used)) static int stb_compress_streaming_start(void)
{
   stb_uint i;
   xtb.size = stb__window * 3;
   xtb.buffer = (stb_uchar*)malloc(xtb.size);
   if (!xtb.buffer) return 0;

   xtb.chash = (stb_uchar**)malloc(sizeof(*xtb.chash) * stb__hashsize);
   if (!xtb.chash) {
      free(xtb.buffer);
      return 0;
   }

   for (i=0; i < stb__hashsize; ++i)
      xtb.chash[i] = NULL;

   xtb.hashmask = stb__hashsize-1;

   xtb.valid        = 0;
   xtb.start        = 0;
   xtb.window       = stb__window;
   xtb.fsize        = stb__window;
   xtb.pending_literals = 0;
   xtb.total_bytes  = 0;

      // stream signature
   stb_out(0x57); stb_out(0xbc); stb_out2(0);

   stb_out4(0);       // 64-bit length requires 32-bit leading 0

   xtb.length_id = (int) stb_out_backpatch_id();
   stb_out4(0);       // we don't know the output length yet

   stb_out4(stb__window);

   stb__running_adler = 1;

   return 1;
}