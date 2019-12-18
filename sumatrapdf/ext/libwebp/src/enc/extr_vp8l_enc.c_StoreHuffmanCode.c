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
typedef  int /*<<< orphan*/  VP8LBitWriter ;
struct TYPE_4__ {int num_symbols; scalar_t__* code_lengths; } ;
typedef  int /*<<< orphan*/  HuffmanTreeToken ;
typedef  TYPE_1__ HuffmanTreeCode ;
typedef  int /*<<< orphan*/  HuffmanTree ;

/* Variables and functions */
 int /*<<< orphan*/  StoreFullHuffmanCode (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,TYPE_1__ const* const) ; 
 int /*<<< orphan*/  VP8LPutBits (int /*<<< orphan*/ * const,int,int) ; 

__attribute__((used)) static void StoreHuffmanCode(VP8LBitWriter* const bw,
                             HuffmanTree* const huff_tree,
                             HuffmanTreeToken* const tokens,
                             const HuffmanTreeCode* const huffman_code) {
  int i;
  int count = 0;
  int symbols[2] = { 0, 0 };
  const int kMaxBits = 8;
  const int kMaxSymbol = 1 << kMaxBits;

  // Check whether it's a small tree.
  for (i = 0; i < huffman_code->num_symbols && count < 3; ++i) {
    if (huffman_code->code_lengths[i] != 0) {
      if (count < 2) symbols[count] = i;
      ++count;
    }
  }

  if (count == 0) {   // emit minimal tree for empty cases
    // bits: small tree marker: 1, count-1: 0, large 8-bit code: 0, code: 0
    VP8LPutBits(bw, 0x01, 4);
  } else if (count <= 2 && symbols[0] < kMaxSymbol && symbols[1] < kMaxSymbol) {
    VP8LPutBits(bw, 1, 1);  // Small tree marker to encode 1 or 2 symbols.
    VP8LPutBits(bw, count - 1, 1);
    if (symbols[0] <= 1) {
      VP8LPutBits(bw, 0, 1);  // Code bit for small (1 bit) symbol value.
      VP8LPutBits(bw, symbols[0], 1);
    } else {
      VP8LPutBits(bw, 1, 1);
      VP8LPutBits(bw, symbols[0], 8);
    }
    if (count == 2) {
      VP8LPutBits(bw, symbols[1], 8);
    }
  } else {
    StoreFullHuffmanCode(bw, huff_tree, tokens, huffman_code);
  }
}