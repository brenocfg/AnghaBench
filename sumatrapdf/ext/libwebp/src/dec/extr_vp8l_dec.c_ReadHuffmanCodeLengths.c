#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ bit_pos_; } ;
struct TYPE_10__ {int /*<<< orphan*/  status_; TYPE_2__ br_; } ;
typedef  TYPE_1__ VP8LDecoder ;
typedef  TYPE_2__ VP8LBitReader ;
struct TYPE_12__ {int value; scalar_t__ bits; } ;
typedef  TYPE_3__ HuffmanCode ;

/* Variables and functions */
 int DEFAULT_CODE_LENGTH ; 
 int LENGTHS_TABLE_BITS ; 
 size_t LENGTHS_TABLE_MASK ; 
 int /*<<< orphan*/  NUM_CODE_LENGTH_CODES ; 
 int /*<<< orphan*/  VP8LBuildHuffmanTable (TYPE_3__*,int,int const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8LFillBitWindow (TYPE_2__* const) ; 
 size_t VP8LPrefetchBits (TYPE_2__* const) ; 
 int const VP8LReadBits (TYPE_2__* const,int const) ; 
 int /*<<< orphan*/  VP8LSetBitPos (TYPE_2__* const,scalar_t__) ; 
 int /*<<< orphan*/  VP8_STATUS_BITSTREAM_ERROR ; 
 int* kCodeLengthExtraBits ; 
 int kCodeLengthLiterals ; 
 int kCodeLengthRepeatCode ; 
 int* kCodeLengthRepeatOffsets ; 

__attribute__((used)) static int ReadHuffmanCodeLengths(
    VP8LDecoder* const dec, const int* const code_length_code_lengths,
    int num_symbols, int* const code_lengths) {
  int ok = 0;
  VP8LBitReader* const br = &dec->br_;
  int symbol;
  int max_symbol;
  int prev_code_len = DEFAULT_CODE_LENGTH;
  HuffmanCode table[1 << LENGTHS_TABLE_BITS];

  if (!VP8LBuildHuffmanTable(table, LENGTHS_TABLE_BITS,
                             code_length_code_lengths,
                             NUM_CODE_LENGTH_CODES)) {
    goto End;
  }

  if (VP8LReadBits(br, 1)) {    // use length
    const int length_nbits = 2 + 2 * VP8LReadBits(br, 3);
    max_symbol = 2 + VP8LReadBits(br, length_nbits);
    if (max_symbol > num_symbols) {
      goto End;
    }
  } else {
    max_symbol = num_symbols;
  }

  symbol = 0;
  while (symbol < num_symbols) {
    const HuffmanCode* p;
    int code_len;
    if (max_symbol-- == 0) break;
    VP8LFillBitWindow(br);
    p = &table[VP8LPrefetchBits(br) & LENGTHS_TABLE_MASK];
    VP8LSetBitPos(br, br->bit_pos_ + p->bits);
    code_len = p->value;
    if (code_len < kCodeLengthLiterals) {
      code_lengths[symbol++] = code_len;
      if (code_len != 0) prev_code_len = code_len;
    } else {
      const int use_prev = (code_len == kCodeLengthRepeatCode);
      const int slot = code_len - kCodeLengthLiterals;
      const int extra_bits = kCodeLengthExtraBits[slot];
      const int repeat_offset = kCodeLengthRepeatOffsets[slot];
      int repeat = VP8LReadBits(br, extra_bits) + repeat_offset;
      if (symbol + repeat > num_symbols) {
        goto End;
      } else {
        const int length = use_prev ? prev_code_len : 0;
        while (repeat-- > 0) code_lengths[symbol++] = length;
      }
    }
  }
  ok = 1;

 End:
  if (!ok) dec->status_ = VP8_STATUS_BITSTREAM_ERROR;
  return ok;
}