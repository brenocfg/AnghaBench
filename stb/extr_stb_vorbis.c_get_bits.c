#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int valid_bits; int acc; } ;
typedef  TYPE_1__ vorb ;
typedef  int uint32 ;

/* Variables and functions */
 int EOP ; 
 int INVALID_BITS ; 
 int get8_packet_raw (TYPE_1__*) ; 

__attribute__((used)) static uint32 get_bits(vorb *f, int n)
{
   uint32 z;

   if (f->valid_bits < 0) return 0;
   if (f->valid_bits < n) {
      if (n > 24) {
         // the accumulator technique below would not work correctly in this case
         z = get_bits(f, 24);
         z += get_bits(f, n-24) << 24;
         return z;
      }
      if (f->valid_bits == 0) f->acc = 0;
      while (f->valid_bits < n) {
         int z = get8_packet_raw(f);
         if (z == EOP) {
            f->valid_bits = INVALID_BITS;
            return 0;
         }
         f->acc += z << f->valid_bits;
         f->valid_bits += 8;
      }
   }
   if (f->valid_bits < 0) return 0;
   z = f->acc & ((1 << n)-1);
   f->acc >>= n;
   f->valid_bits -= n;
   return z;
}