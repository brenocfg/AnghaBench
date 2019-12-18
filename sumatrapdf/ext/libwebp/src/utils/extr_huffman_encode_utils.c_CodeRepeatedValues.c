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
struct TYPE_4__ {int code; int extra_bits; } ;
typedef  TYPE_1__ HuffmanTreeToken ;

/* Variables and functions */
 int MAX_ALLOWED_CODE_LENGTH ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static HuffmanTreeToken* CodeRepeatedValues(int repetitions,
                                            HuffmanTreeToken* tokens,
                                            int value, int prev_value) {
  assert(value <= MAX_ALLOWED_CODE_LENGTH);
  if (value != prev_value) {
    tokens->code = value;
    tokens->extra_bits = 0;
    ++tokens;
    --repetitions;
  }
  while (repetitions >= 1) {
    if (repetitions < 3) {
      int i;
      for (i = 0; i < repetitions; ++i) {
        tokens->code = value;
        tokens->extra_bits = 0;
        ++tokens;
      }
      break;
    } else if (repetitions < 7) {
      tokens->code = 16;
      tokens->extra_bits = repetitions - 3;
      ++tokens;
      break;
    } else {
      tokens->code = 16;
      tokens->extra_bits = 3;
      ++tokens;
      repetitions -= 6;
    }
  }
  return tokens;
}