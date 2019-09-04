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

/* Variables and functions */
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  rbsize_add_band (int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  rbsize_add_row (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rbsize_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/ * rbsize_results ; 
 int rbsize_results_num ; 
 int string_width (char*) ; 
 int system_font_height ; 

__attribute__((used)) static void rbsize_results_init(void)
{
    rbsize_results = heap_alloc(rbsize_results_num * sizeof(*rbsize_results));

    rbsize_results[0] = rbsize_init(0, 0, 672, 0, 0, 0, 0);

    rbsize_results[1] = rbsize_init(0, 0, 672, 4, 4, 1, 1);
    rbsize_add_row(&rbsize_results[1], 4);
    rbsize_add_band(&rbsize_results[1], 0, 0, 672, 4, 0x00, 200);

    rbsize_results[2] = rbsize_init(0, 0, 672, 4, 4, 1, 2);
    rbsize_add_row(&rbsize_results[2], 4);
    rbsize_add_band(&rbsize_results[2], 0, 0, 200, 4, 0x00, 200);
    rbsize_add_band(&rbsize_results[2], 200, 0, 672, 4, 0x04, 200);

    rbsize_results[3] = rbsize_init(0, 0, 672, 30, 30, 1, 3);
    rbsize_add_row(&rbsize_results[3], 30);
    rbsize_add_band(&rbsize_results[3], 0, 0, 200, 30, 0x00, 200);
    rbsize_add_band(&rbsize_results[3], 200, 0, 400, 30, 0x04, 200);
    rbsize_add_band(&rbsize_results[3], 400, 0, 672, 30, 0x00, 200);

    rbsize_results[4] = rbsize_init(0, 0, 672, 34, 34, 1, 4);
    rbsize_add_row(&rbsize_results[4], 34);
    rbsize_add_band(&rbsize_results[4], 0, 0, 200, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[4], 200, 0, 400, 34, 0x04, 200);
    rbsize_add_band(&rbsize_results[4], 400, 0, 604, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[4], 604, 0, 672, 34, 0x04, 68);

    rbsize_results[5] = rbsize_init(0, 0, 672, 34, 34, 1, 4);
    rbsize_add_row(&rbsize_results[5], 34);
    rbsize_add_band(&rbsize_results[5], 0, 0, 200, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[5], 200, 0, 400, 34, 0x04, 200);
    rbsize_add_band(&rbsize_results[5], 400, 0, 604, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[5], 604, 0, 672, 34, 0x04, 68);

    rbsize_results[6] = rbsize_init(0, 0, 672, 34, 34, 1, 4);
    rbsize_add_row(&rbsize_results[6], 34);
    rbsize_add_band(&rbsize_results[6], 0, 0, 200, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[6], 202, 0, 402, 34, 0x04, 200);
    rbsize_add_band(&rbsize_results[6], 404, 0, 604, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[6], 606, 0, 672, 34, 0x04, 66);

    rbsize_results[7] = rbsize_init(0, 0, 672, 70, 70, 2, 5);
    rbsize_add_row(&rbsize_results[7], 34);
    rbsize_add_row(&rbsize_results[7], 34);
    rbsize_add_band(&rbsize_results[7], 0, 0, 142, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[7], 144, 0, 557, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[7], 559, 0, 672, 34, 0x04, 200);
    rbsize_add_band(&rbsize_results[7], 0, 36, 200, 70, 0x00, 200);
    rbsize_add_band(&rbsize_results[7], 202, 36, 672, 70, 0x04, 66);

    rbsize_results[8] = rbsize_init(0, 0, 672, 34, 34, 1, 5);
    rbsize_add_row(&rbsize_results[8], 34);
    rbsize_add_band(&rbsize_results[8], 0, 0, 167, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[8], 169, 0, 582, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[8], 559, 0, 759, 34, 0x08, 200);
    rbsize_add_band(&rbsize_results[8], 584, 0, 627, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[8], 629, 0, 672, 34, 0x04, 66);

    rbsize_results[9] = rbsize_init(0, 0, 672, 34, 34, 1, 4);
    rbsize_add_row(&rbsize_results[9], 34);
    rbsize_add_band(&rbsize_results[9], 0, 0, 167, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[9], 169, 0, 582, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[9], 584, 0, 627, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[9], 629, 0, 672, 34, 0x04, 66);

    rbsize_results[10] = rbsize_init(0, 0, 672, 34, 34, 1, 3);
    rbsize_add_row(&rbsize_results[10], 34);
    rbsize_add_band(&rbsize_results[10], 0, 0, 413, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[10], 415, 0, 615, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[10], 617, 0, 672, 34, 0x04, 66);

    rbsize_results[11] = rbsize_init(0, 0, 672, 34, 34, 1, 2);
    rbsize_add_row(&rbsize_results[11], 34);
    rbsize_add_band(&rbsize_results[11], 0, 0, 604, 34, 0x00, 200);
    rbsize_add_band(&rbsize_results[11], 606, 0, 672, 34, 0x04, 66);

    rbsize_results[12] = rbsize_init(0, 0, 672, 8 + 2*system_font_height, 40, 2, 5);
    rbsize_add_row(&rbsize_results[12], 4 + system_font_height);
    rbsize_add_row(&rbsize_results[12], 4 + system_font_height);
    rbsize_add_band(&rbsize_results[12], 0, 0, 87 + string_width("ABC"), 4 + system_font_height, 0x00, 40);
    rbsize_add_band(&rbsize_results[12], 87 + string_width("ABC"), 0, 157 + string_width("ABC"), 4 + system_font_height, 0x00, 70);
    rbsize_add_band(&rbsize_results[12], 157 + string_width("ABC"), 0, 397 + string_width("ABC"), 4 + system_font_height, 0x00, 240);
    rbsize_add_band(&rbsize_results[12], 397 + string_width("ABC"), 0, 672, 4 + system_font_height, 0x00, 60);
    rbsize_add_band(&rbsize_results[12], 0, 4 + system_font_height, 672, 8 + 2*system_font_height, 0x00, 200);

    rbsize_results[13] = rbsize_init(0, 0, 672, 8 + 2*system_font_height, 40, 2, 5);
    rbsize_add_row(&rbsize_results[13], 4 + system_font_height);
    rbsize_add_row(&rbsize_results[13], 4 + system_font_height);
    rbsize_add_band(&rbsize_results[13], 0, 0, 87 + string_width("ABC"), 4 + system_font_height, 0x00, 40);
    rbsize_add_band(&rbsize_results[13], 87 + string_width("ABC"), 0, 200 + string_width("ABC"), 4 + system_font_height, 0x00, 113);
    rbsize_add_band(&rbsize_results[13], 200 + string_width("ABC"), 0, 397 + string_width("ABC"), 4 + system_font_height, 0x00, 197);
    rbsize_add_band(&rbsize_results[13], 397 + string_width("ABC"), 0, 672, 4 + system_font_height, 0x00, 60);
    rbsize_add_band(&rbsize_results[13], 0, 4 + system_font_height, 672, 8 + 2*system_font_height, 0x00, 200);

    rbsize_results[14] = rbsize_init(0, 0, 672, 8 + 2*system_font_height, 40, 2, 5);
    rbsize_add_row(&rbsize_results[14], 4 + system_font_height);
    rbsize_add_row(&rbsize_results[14], 4 + system_font_height);
    rbsize_add_band(&rbsize_results[14], 0, 0, 87 + string_width("ABC"), 4 + system_font_height, 0x00, 40);
    rbsize_add_band(&rbsize_results[14], 87 + string_width("ABC"), 0, 412 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 325 - string_width("ABC") - string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[14], 412 - string_width("MMMMMMM"), 0, 595 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 183);
    rbsize_add_band(&rbsize_results[14], 595 - string_width("MMMMMMM"), 0, 672, 4 + system_font_height, 0x00, 77 + string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[14], 0, 4 + system_font_height, 672, 8 + 2*system_font_height, 0x00, 200);

    rbsize_results[15] = rbsize_init(0, 0, 672, 8 + 2*system_font_height, 40, 2, 5);
    rbsize_add_row(&rbsize_results[15], 4 + system_font_height);
    rbsize_add_row(&rbsize_results[15], 4 + system_font_height);
    rbsize_add_band(&rbsize_results[15], 0, 0, 87 + string_width("ABC"), 4 + system_font_height, 0x00, 40);
    rbsize_add_band(&rbsize_results[15], 87 + string_width("ABC"), 0, 140 + string_width("ABC"), 4 + system_font_height, 0x00, 53);
    rbsize_add_band(&rbsize_results[15], 140 + string_width("ABC"), 0, 595 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 455 - string_width("MMMMMMM") - string_width("ABC"));
    rbsize_add_band(&rbsize_results[15], 595 - string_width("MMMMMMM"), 0, 672, 4 + system_font_height, 0x00, 77 + string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[15], 0, 4 + system_font_height, 672, 8 + 2*system_font_height, 0x00, 200);

    rbsize_results[16] = rbsize_init(0, 0, 672, 8 + 2*system_font_height, 40, 2, 5);
    rbsize_add_row(&rbsize_results[16], 4 + system_font_height);
    rbsize_add_row(&rbsize_results[16], 4 + system_font_height);
    rbsize_add_band(&rbsize_results[16], 0, 0, 87 + string_width("ABC"), 4 + system_font_height, 0x00, 40);
    rbsize_add_band(&rbsize_results[16], 87 + string_width("ABC"), 0, 412 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 325 - string_width("ABC") - string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[16], 412 - string_width("MMMMMMM"), 0, 595 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 183);
    rbsize_add_band(&rbsize_results[16], 595 - string_width("MMMMMMM"), 0, 672, 4 + system_font_height, 0x00, 77 + string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[16], 0, 4 + system_font_height, 672, 8 + 2*system_font_height, 0x00, 200);

    rbsize_results[17] = rbsize_init(0, 0, 672, 8 + 2*system_font_height, 40, 2, 5);
    rbsize_add_row(&rbsize_results[17], 4 + system_font_height);
    rbsize_add_row(&rbsize_results[17], 4 + system_font_height);
    rbsize_add_band(&rbsize_results[17], 0, 0, 87 + string_width("ABC"), 4 + system_font_height, 0x00, 40);
    rbsize_add_band(&rbsize_results[17], 87 + string_width("ABC"), 0, 412 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 325 - string_width("ABC") - string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[17], 412 - string_width("MMMMMMM"), 0, 595 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 183);
    rbsize_add_band(&rbsize_results[17], 595 - string_width("MMMMMMM"), 0, 672, 4 + system_font_height, 0x00, 77 + string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[17], 0, 4 + system_font_height, 672, 8 + 2*system_font_height, 0x00, 200);

    rbsize_results[18] = rbsize_init(0, 0, 672, 56, 56, 2, 5);
    rbsize_add_row(&rbsize_results[18], 28);
    rbsize_add_row(&rbsize_results[18], 28);
    rbsize_add_band(&rbsize_results[18], 0, 0, 87 + string_width("ABC"), 28, 0x00, 40);
    rbsize_add_band(&rbsize_results[18], 87 + string_width("ABC"), 0, 412 - string_width("MMMMMMM"), 28, 0x00, 325 - string_width("ABC") - string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[18], 412 - string_width("MMMMMMM"), 0, 595 - string_width("MMMMMMM"), 28, 0x00, 183);
    rbsize_add_band(&rbsize_results[18], 595 - string_width("MMMMMMM"), 0, 672, 28, 0x00, 77 + string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[18], 0, 28, 672, 56, 0x00, 200);

    rbsize_results[19] = rbsize_init(0, 0, 672, 8 + 2*system_font_height, 40, 2, 5);
    rbsize_add_row(&rbsize_results[19], 4 + system_font_height);
    rbsize_add_row(&rbsize_results[19], 4 + system_font_height);
    rbsize_add_band(&rbsize_results[19], 0, 0, 87 + string_width("ABC"), 4 + system_font_height, 0x00, 40);
    rbsize_add_band(&rbsize_results[19], 87 + string_width("ABC"), 0, 412 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 325 - string_width("ABC") - string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[19], 412 - string_width("MMMMMMM"), 0, 595 - string_width("MMMMMMM"), 4 + system_font_height, 0x00, 183);
    rbsize_add_band(&rbsize_results[19], 595 - string_width("MMMMMMM"), 0, 672, 4 + system_font_height, 0x00, 77 + string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[19], 0, 4 + system_font_height, 672, 8 + 2*system_font_height, 0x00, 200);

    rbsize_results[20] = rbsize_init(0, 0, 672, 56, 56, 2, 5);
    rbsize_add_row(&rbsize_results[20], 28);
    rbsize_add_row(&rbsize_results[20], 28);
    rbsize_add_band(&rbsize_results[20], 0, 0, 87 + string_width("ABC"), 28, 0x00, 40);
    rbsize_add_band(&rbsize_results[20], 87 + string_width("ABC"), 0, 412 - string_width("MMMMMMM"), 28, 0x00, 325 - string_width("ABC") - string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[20], 412 - string_width("MMMMMMM"), 0,  595 - string_width("MMMMMMM"), 28, 0x00, 183);
    rbsize_add_band(&rbsize_results[20],  595 - string_width("MMMMMMM"), 0, 672, 28, 0x00, 77 + string_width("MMMMMMM"));
    rbsize_add_band(&rbsize_results[20], 0, 28, 672, 56, 0x00, 200);

    rbsize_results[21] = rbsize_init(0, 0, 672, 0, 0, 0, 0);

    rbsize_results[22] = rbsize_init(0, 0, 672, 65, 56, 1, 3);
    rbsize_add_row(&rbsize_results[22], 65);
    rbsize_add_band(&rbsize_results[22], 0, 0, 90, 65, 0x40, 90);
    rbsize_add_band(&rbsize_results[22], 90, 0, 180, 65, 0x40, 90);
    rbsize_add_band(&rbsize_results[22], 180, 0, 672, 65, 0x40, 90);

    rbsize_results[23] = rbsize_init(0, 0, 0, 226, 0, 0, 0);

    rbsize_results[24] = rbsize_init(0, 0, 65, 226, 65, 1, 1);
    rbsize_add_row(&rbsize_results[24], 65);
    rbsize_add_band(&rbsize_results[24], 0, 0, 226, 65, 0x40, 90);

    rbsize_results[25] = rbsize_init(0, 0, 65, 226, 65, 1, 2);
    rbsize_add_row(&rbsize_results[25], 65);
    rbsize_add_band(&rbsize_results[25], 0, 0, 90, 65, 0x40, 90);
    rbsize_add_band(&rbsize_results[25], 90, 0, 226, 65, 0x40, 90);

    rbsize_results[26] = rbsize_init(0, 0, 65, 226, 65, 1, 3);
    rbsize_add_row(&rbsize_results[26], 65);
    rbsize_add_band(&rbsize_results[26], 0, 0, 90, 65, 0x40, 90);
    rbsize_add_band(&rbsize_results[26], 90, 0, 163, 65, 0x40, 90);
    rbsize_add_band(&rbsize_results[26], 163, 0, 226, 65, 0x40, 90);
}