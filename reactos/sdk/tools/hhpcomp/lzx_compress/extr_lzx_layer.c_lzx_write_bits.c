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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int bits_in_buf; int bit_buf; int len_compressed_output; int /*<<< orphan*/  out_arg; int /*<<< orphan*/  (* put_bytes ) (int /*<<< orphan*/ ,int,int*) ;} ;
typedef  TYPE_1__ lzx_data ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void lzx_write_bits(lzx_data *lzxd, int nbits, uint32_t bits)
{
  int cur_bits;
  int shift_bits;
  int rshift_bits;
  uint16_t mask_bits;

#ifdef DEBUG_BITBUF
  fprintf(stderr, "WB: %2d %08x\n", nbits, bits);
#endif
  cur_bits = lzxd->bits_in_buf;
  while ((cur_bits + nbits) >= 16) {
    shift_bits = 16 - cur_bits;
    rshift_bits = nbits - shift_bits;
    if (shift_bits == 16) {
      lzxd->bit_buf = (bits>>rshift_bits) & 0xFFFF;
    }
    else {
      mask_bits = (1U << shift_bits) - 1;
      lzxd->bit_buf <<= shift_bits;
      lzxd->bit_buf |= (bits>>rshift_bits) & mask_bits;
    }
#ifdef DEBUG_BITBUF
    fprintf(stderr, "WBB: %04x\n", lzxd->bit_buf);
#endif
#ifdef LZX_BIG_ENDIAN
    lzxd->bit_buf = ((lzxd->bit_buf & 0xFF)<<8) | (lzxd->bit_buf >> 8);
#endif
    lzxd->put_bytes(lzxd->out_arg, sizeof(lzxd->bit_buf), &lzxd->bit_buf);
    lzxd->len_compressed_output += sizeof(lzxd->bit_buf);
    lzxd->bit_buf = 0;
    nbits -= shift_bits;
    cur_bits = 0;
  }
  /* (cur_bits + nbits) < 16.  If nbits = 0, we're done. 
     otherwise move bits in */
  shift_bits = nbits;
  mask_bits = (1U << shift_bits) - 1;
  lzxd->bit_buf <<= shift_bits;
  lzxd->bit_buf |= bits & mask_bits;
  cur_bits += nbits;

#ifdef DEBUG_BITBUF
  fprintf(stderr, "OBB: %2d %04x\n", cur_bits, lzxd->bit_buf);
#endif
  lzxd->bits_in_buf = cur_bits;
}