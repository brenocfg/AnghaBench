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
struct lzw_state {int /*<<< orphan*/  clear_code; } ;

/* Variables and functions */
 int lzw_output_code (struct lzw_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int lzw_output_clear_code(struct lzw_state *state)
{
    return lzw_output_code(state, state->clear_code);
}