#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_3__ {int refcount; unsigned char** blockdata; unsigned char** data; } ;
typedef  TYPE_1__ fast_chunk ;

/* Variables and functions */
 int C_empty ; 
 int /*<<< orphan*/  assert (int) ; 

void make_converted_fastchunk(fast_chunk *fc, int x, int y, int segment, uint8 *sv_blocktype, uint8 *sv_lighting)
{
   int z;
   assert(fc == NULL || (fc->refcount > 0 && fc->refcount < 64));
   if (fc == NULL || fc->blockdata[segment] == NULL) {
      for (z=0; z < 16; ++z) {
         sv_blocktype[z] = C_empty;
         sv_lighting[z] = 255;
      }
   } else {
      unsigned char *block = fc->blockdata[segment];
      unsigned char *data  = fc->data[segment];
      y = 15-y;
      for (z=0; z < 16; ++z) {
         sv_blocktype[z] = block[z*256 + y*16 + x];
         sv_lighting [z] = data [z*256 + y*16 + x];
      }
   }
}