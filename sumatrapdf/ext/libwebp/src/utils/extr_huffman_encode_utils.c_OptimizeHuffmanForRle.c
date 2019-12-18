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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ValuesShouldBeCollapsedToStrideAverage (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void OptimizeHuffmanForRle(int length, uint8_t* const good_for_rle,
                                  uint32_t* const counts) {
  // 1) Let's make the Huffman code more compatible with rle encoding.
  int i;
  for (; length >= 0; --length) {
    if (length == 0) {
      return;  // All zeros.
    }
    if (counts[length - 1] != 0) {
      // Now counts[0..length - 1] does not have trailing zeros.
      break;
    }
  }
  // 2) Let's mark all population counts that already can be encoded
  // with an rle code.
  {
    // Let's not spoil any of the existing good rle codes.
    // Mark any seq of 0's that is longer as 5 as a good_for_rle.
    // Mark any seq of non-0's that is longer as 7 as a good_for_rle.
    uint32_t symbol = counts[0];
    int stride = 0;
    for (i = 0; i < length + 1; ++i) {
      if (i == length || counts[i] != symbol) {
        if ((symbol == 0 && stride >= 5) ||
            (symbol != 0 && stride >= 7)) {
          int k;
          for (k = 0; k < stride; ++k) {
            good_for_rle[i - k - 1] = 1;
          }
        }
        stride = 1;
        if (i != length) {
          symbol = counts[i];
        }
      } else {
        ++stride;
      }
    }
  }
  // 3) Let's replace those population counts that lead to more rle codes.
  {
    uint32_t stride = 0;
    uint32_t limit = counts[0];
    uint32_t sum = 0;
    for (i = 0; i < length + 1; ++i) {
      if (i == length || good_for_rle[i] ||
          (i != 0 && good_for_rle[i - 1]) ||
          !ValuesShouldBeCollapsedToStrideAverage(counts[i], limit)) {
        if (stride >= 4 || (stride >= 3 && sum == 0)) {
          uint32_t k;
          // The stride must end, collapse what we have, if we have enough (4).
          uint32_t count = (sum + stride / 2) / stride;
          if (count < 1) {
            count = 1;
          }
          if (sum == 0) {
            // Don't make an all zeros stride to be upgraded to ones.
            count = 0;
          }
          for (k = 0; k < stride; ++k) {
            // We don't want to change value at counts[i],
            // that is already belonging to the next stride. Thus - 1.
            counts[i - k - 1] = count;
          }
        }
        stride = 0;
        sum = 0;
        if (i < length - 3) {
          // All interesting strides have a count of at least 4,
          // at least when non-zeros.
          limit = (counts[i] + counts[i + 1] +
                   counts[i + 2] + counts[i + 3] + 2) / 4;
        } else if (i < length) {
          limit = counts[i];
        } else {
          limit = 0;
        }
      }
      ++stride;
      if (i != length) {
        sum += counts[i];
        if (stride >= 4) {
          limit = (sum + stride / 2) / stride;
        }
      }
    }
  }
}