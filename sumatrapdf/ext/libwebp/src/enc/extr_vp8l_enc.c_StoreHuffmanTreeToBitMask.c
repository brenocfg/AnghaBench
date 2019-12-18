#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VP8LBitWriter ;
struct TYPE_6__ {int const* codes; int* code_lengths; } ;
struct TYPE_5__ {int code; int extra_bits; } ;
typedef  TYPE_1__ HuffmanTreeToken ;
typedef  TYPE_2__ HuffmanTreeCode ;

/* Variables and functions */
 int /*<<< orphan*/  VP8LPutBits (int /*<<< orphan*/ * const,int const,int) ; 

__attribute__((used)) static void StoreHuffmanTreeToBitMask(
    VP8LBitWriter* const bw,
    const HuffmanTreeToken* const tokens, const int num_tokens,
    const HuffmanTreeCode* const huffman_code) {
  int i;
  for (i = 0; i < num_tokens; ++i) {
    const int ix = tokens[i].code;
    const int extra_bits = tokens[i].extra_bits;
    VP8LPutBits(bw, huffman_code->codes[ix], huffman_code->code_lengths[ix]);
    switch (ix) {
      case 16:
        VP8LPutBits(bw, extra_bits, 2);
        break;
      case 17:
        VP8LPutBits(bw, extra_bits, 3);
        break;
      case 18:
        VP8LPutBits(bw, extra_bits, 7);
        break;
    }
  }
}