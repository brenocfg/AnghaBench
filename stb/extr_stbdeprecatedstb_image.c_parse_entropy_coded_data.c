#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int scan_n; int* order; scalar_t__ todo; int code_bits; int img_mcu_y; int img_mcu_x; int /*<<< orphan*/  marker; TYPE_1__* img_comp; int /*<<< orphan*/ * dequant; scalar_t__ huff_ac; scalar_t__ huff_dc; } ;
typedef  TYPE_2__ jpeg ;
struct TYPE_7__ {int x; int y; int w2; size_t tq; int v; int h; scalar_t__ data; scalar_t__ ha; scalar_t__ hd; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESTART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_block (TYPE_2__*,short*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  grow_buffer_unsafe (TYPE_2__*) ; 
 int /*<<< orphan*/  idct_block (scalar_t__,int,short*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset (TYPE_2__*) ; 

__attribute__((used)) static int parse_entropy_coded_data(jpeg *z)
{
   reset(z);
   if (z->scan_n == 1) {
      int i,j;
      #ifdef STBI_SIMD
      __declspec(align(16))
      #endif
      short data[64];
      int n = z->order[0];
      // non-interleaved data, we just need to process one block at a time,
      // in trivial scanline order
      // number of blocks to do just depends on how many actual "pixels" this
      // component has, independent of interleaved MCU blocking and such
      int w = (z->img_comp[n].x+7) >> 3;
      int h = (z->img_comp[n].y+7) >> 3;
      for (j=0; j < h; ++j) {
         for (i=0; i < w; ++i) {
            if (!decode_block(z, data, z->huff_dc+z->img_comp[n].hd, z->huff_ac+z->img_comp[n].ha, n)) return 0;
            #ifdef STBI_SIMD
            stbi_idct_installed(z->img_comp[n].data+z->img_comp[n].w2*j*8+i*8, z->img_comp[n].w2, data, z->dequant2[z->img_comp[n].tq]);
            #else
            idct_block(z->img_comp[n].data+z->img_comp[n].w2*j*8+i*8, z->img_comp[n].w2, data, z->dequant[z->img_comp[n].tq]);
            #endif
            // every data block is an MCU, so countdown the restart interval
            if (--z->todo <= 0) {
               if (z->code_bits < 24) grow_buffer_unsafe(z);
               // if it's NOT a restart, then just bail, so we get corrupt data
               // rather than no data
               if (!RESTART(z->marker)) return 1;
               reset(z);
            }
         }
      }
   } else { // interleaved!
      int i,j,k,x,y;
      short data[64];
      for (j=0; j < z->img_mcu_y; ++j) {
         for (i=0; i < z->img_mcu_x; ++i) {
            // scan an interleaved mcu... process scan_n components in order
            for (k=0; k < z->scan_n; ++k) {
               int n = z->order[k];
               // scan out an mcu's worth of this component; that's just determined
               // by the basic H and V specified for the component
               for (y=0; y < z->img_comp[n].v; ++y) {
                  for (x=0; x < z->img_comp[n].h; ++x) {
                     int x2 = (i*z->img_comp[n].h + x)*8;
                     int y2 = (j*z->img_comp[n].v + y)*8;
                     if (!decode_block(z, data, z->huff_dc+z->img_comp[n].hd, z->huff_ac+z->img_comp[n].ha, n)) return 0;
                     #ifdef STBI_SIMD
                     stbi_idct_installed(z->img_comp[n].data+z->img_comp[n].w2*y2+x2, z->img_comp[n].w2, data, z->dequant2[z->img_comp[n].tq]);
                     #else
                     idct_block(z->img_comp[n].data+z->img_comp[n].w2*y2+x2, z->img_comp[n].w2, data, z->dequant[z->img_comp[n].tq]);
                     #endif
                  }
               }
            }
            // after all interleaved components, that's an interleaved MCU,
            // so now count down the restart interval
            if (--z->todo <= 0) {
               if (z->code_bits < 24) grow_buffer_unsafe(z);
               // if it's NOT a restart, then just bail, so we get corrupt data
               // rather than no data
               if (!RESTART(z->marker)) return 1;
               reset(z);
            }
         }
      }
   }
   return 1;
}