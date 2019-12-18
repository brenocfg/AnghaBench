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
struct TYPE_7__ {int acc; int valid_bits; } ;
typedef  TYPE_1__ vorb ;
typedef  scalar_t__ uint32 ;
struct TYPE_8__ {int* codewords; scalar_t__* sorted_codewords; int entries; int sorted_entries; int* sorted_values; int* codeword_lengths; int /*<<< orphan*/  sparse; } ;
typedef  TYPE_2__ Codebook ;

/* Variables and functions */
 int NO_CODE ; 
 int /*<<< orphan*/  VORBIS_invalid_stream ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bit_reverse (int) ; 
 int /*<<< orphan*/  error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prep_huffman (TYPE_1__*) ; 

__attribute__((used)) static int codebook_decode_scalar_raw(vorb *f, Codebook *c)
{
   int i;
   prep_huffman(f);

   if (c->codewords == NULL && c->sorted_codewords == NULL)
      return -1;

   // cases to use binary search: sorted_codewords && !c->codewords
   //                             sorted_codewords && c->entries > 8
   if (c->entries > 8 ? c->sorted_codewords!=NULL : !c->codewords) {
      // binary search
      uint32 code = bit_reverse(f->acc);
      int x=0, n=c->sorted_entries, len;

      while (n > 1) {
         // invariant: sc[x] <= code < sc[x+n]
         int m = x + (n >> 1);
         if (c->sorted_codewords[m] <= code) {
            x = m;
            n -= (n>>1);
         } else {
            n >>= 1;
         }
      }
      // x is now the sorted index
      if (!c->sparse) x = c->sorted_values[x];
      // x is now sorted index if sparse, or symbol otherwise
      len = c->codeword_lengths[x];
      if (f->valid_bits >= len) {
         f->acc >>= len;
         f->valid_bits -= len;
         return x;
      }

      f->valid_bits = 0;
      return -1;
   }

   // if small, linear search
   assert(!c->sparse);
   for (i=0; i < c->entries; ++i) {
      if (c->codeword_lengths[i] == NO_CODE) continue;
      if (c->codewords[i] == (f->acc & ((1 << c->codeword_lengths[i])-1))) {
         if (f->valid_bits >= c->codeword_lengths[i]) {
            f->acc >>= c->codeword_lengths[i];
            f->valid_bits -= c->codeword_lengths[i];
            return i;
         }
         f->valid_bits = 0;
         return -1;
      }
   }

   error(f, VORBIS_invalid_stream);
   f->valid_bits = 0;
   return -1;
}