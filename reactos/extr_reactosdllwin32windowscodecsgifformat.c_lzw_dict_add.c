#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {short* prefix; unsigned char* suffix; } ;
struct lzw_state {size_t next_code; int /*<<< orphan*/  code_bits; TYPE_1__ dict; } ;

/* Variables and functions */
 size_t LZW_DICT_SIZE ; 

__attribute__((used)) static int lzw_dict_add(struct lzw_state *state, short prefix, unsigned char suffix)
{
    if (state->next_code < LZW_DICT_SIZE)
    {
        state->dict.prefix[state->next_code] = prefix;
        state->dict.suffix[state->next_code] = suffix;

        if ((state->next_code & (state->next_code - 1)) == 0)
            state->code_bits++;

        state->next_code++;
        return state->next_code;
    }

    return -1;
}