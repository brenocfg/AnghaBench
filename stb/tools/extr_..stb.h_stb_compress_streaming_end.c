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
struct TYPE_2__ {scalar_t__ chash; scalar_t__ buffer; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  length_id; scalar_t__ pending_literals; scalar_t__ valid; int /*<<< orphan*/  hashmask; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  outliterals (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stb__running_adler ; 
 int /*<<< orphan*/  stb_compress_chunk (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_out2 (int) ; 
 int /*<<< orphan*/  stb_out4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_out_backpatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ xtb ; 

__attribute__((used)) static int stb_compress_streaming_end(void)
{
   // flush out any remaining data
   stb_compress_chunk(xtb.buffer, xtb.buffer+xtb.start, xtb.buffer+xtb.valid,
                      xtb.valid-xtb.start, &xtb.pending_literals, xtb.chash, xtb.hashmask);

   // write out pending literals
   outliterals(xtb.buffer + xtb.valid - xtb.pending_literals, xtb.pending_literals);

   stb_out2(0x05fa); // end opcode
   stb_out4(stb__running_adler);

   stb_out_backpatch(xtb.length_id, xtb.total_bytes);

   free(xtb.buffer);
   free(xtb.chash);
   return 1;
}