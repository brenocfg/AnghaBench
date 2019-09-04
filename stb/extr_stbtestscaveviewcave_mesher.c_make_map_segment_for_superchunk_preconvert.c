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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  fast_chunk ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  make_converted_fastchunk (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void make_map_segment_for_superchunk_preconvert(int chunk_x, int chunk_y, int segment, fast_chunk *fc_table[4][4], uint8 sv_blocktype[34][34][18], uint8 sv_lighting[34][34][18])
{
   int a,b;
   assert((chunk_x & 1) == 0);
   assert((chunk_y & 1) == 0);
   for (b=-1; b < 3; ++b) {
      for (a=-1; a < 3; ++a) {
         int xo = a*16+1;
         int yo = b*16+1;
         int x,y;
         fast_chunk *fc = fc_table[b+1][a+1];
         for (y=0; y < 16; ++y)
            for (x=0; x < 16; ++x)
               if (xo+x >= 0 && xo+x < 34 && yo+y >= 0 && yo+y < 34)
                  make_converted_fastchunk(fc,x,y, segment, sv_blocktype[xo+x][yo+y], sv_lighting[xo+x][yo+y]);
      }
   }
}