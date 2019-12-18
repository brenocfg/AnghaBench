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
struct TYPE_3__ {int num_symbols; int* code_lengths; } ;
typedef  int /*<<< orphan*/  HuffmanTreeToken ;
typedef  TYPE_1__ HuffmanTreeCode ;

/* Variables and functions */
 int /*<<< orphan*/ * CodeRepeatedValues (int,int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/ * CodeRepeatedZeros (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

int VP8LCreateCompressedHuffmanTree(const HuffmanTreeCode* const tree,
                                    HuffmanTreeToken* tokens, int max_tokens) {
  HuffmanTreeToken* const starting_token = tokens;
  HuffmanTreeToken* const ending_token = tokens + max_tokens;
  const int depth_size = tree->num_symbols;
  int prev_value = 8;  // 8 is the initial value for rle.
  int i = 0;
  assert(tokens != NULL);
  while (i < depth_size) {
    const int value = tree->code_lengths[i];
    int k = i + 1;
    int runs;
    while (k < depth_size && tree->code_lengths[k] == value) ++k;
    runs = k - i;
    if (value == 0) {
      tokens = CodeRepeatedZeros(runs, tokens);
    } else {
      tokens = CodeRepeatedValues(runs, tokens, value, prev_value);
      prev_value = value;
    }
    i += runs;
    assert(tokens <= ending_token);
  }
  (void)ending_token;    // suppress 'unused variable' warning
  return (int)(tokens - starting_token);
}