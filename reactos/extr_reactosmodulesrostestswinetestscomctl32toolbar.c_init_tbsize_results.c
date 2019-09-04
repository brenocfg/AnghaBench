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
 int /*<<< orphan*/  STRING1 ; 
 int /*<<< orphan*/  STRING2 ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_tbsize_result (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int string_width (int /*<<< orphan*/ ) ; 
 int system_font_height () ; 
 int /*<<< orphan*/  tbsize_addbutton (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * tbsize_results ; 
 int tbsize_results_num ; 

__attribute__((used)) static void init_tbsize_results(void) {
    int fontheight = system_font_height();
    int buttonwidth;

    tbsize_results = heap_alloc_zero(tbsize_results_num * sizeof(*tbsize_results));

    tbsize_results[0] = init_tbsize_result(5, 0, 0 ,672 ,26, 100 ,22);
    tbsize_addbutton(&tbsize_results[0],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[0],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[0],  46,   2,  54,  24);
    tbsize_addbutton(&tbsize_results[0],  54,   2,  77,  24);
    tbsize_addbutton(&tbsize_results[0],  77,   2, 100,  24);

    tbsize_results[1] = init_tbsize_result(7, 0, 0, 672, 26, 146, 22);
    tbsize_addbutton(&tbsize_results[1],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[1],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[1],  46,   2,  54,  24);
    tbsize_addbutton(&tbsize_results[1],  54,   2,  77,  24);
    tbsize_addbutton(&tbsize_results[1],  77,   2, 100,  24);
    tbsize_addbutton(&tbsize_results[1], 100,   2, 123,  24);
    tbsize_addbutton(&tbsize_results[1],   0,   24, 23,  46);

    tbsize_results[2] = init_tbsize_result(7, 0, 0, 672, 26, 146, 22);
    tbsize_addbutton(&tbsize_results[2],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[2],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[2],  46,   2,  54,  24);
    tbsize_addbutton(&tbsize_results[2],  54,   2,  77,  24);
    tbsize_addbutton(&tbsize_results[2],  77,   2, 100,  24);
    tbsize_addbutton(&tbsize_results[2], 100,   2, 123,  24);
    tbsize_addbutton(&tbsize_results[2],   0,   24, 23,  46);

    tbsize_results[3] = init_tbsize_result(7, 0, 0, 672, 26, 146, 22);
    tbsize_addbutton(&tbsize_results[3],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[3],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[3],  46,   2,  54,  24);
    tbsize_addbutton(&tbsize_results[3],  54,   2,  77,  24);
    tbsize_addbutton(&tbsize_results[3],  77,   2, 100,  24);
    tbsize_addbutton(&tbsize_results[3], 100,   2, 123,  24);
    tbsize_addbutton(&tbsize_results[3], 123,   2, 146,  24);

    tbsize_results[4] = init_tbsize_result(9, 0, 0, 672, 26, 192, 22);
    tbsize_addbutton(&tbsize_results[4],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[4],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[4],  46,   2,  54,  24);
    tbsize_addbutton(&tbsize_results[4],  54,   2,  77,  24);
    tbsize_addbutton(&tbsize_results[4],  77,   2, 100,  24);
    tbsize_addbutton(&tbsize_results[4], 100,   2, 123,  24);
    tbsize_addbutton(&tbsize_results[4], 123,   2, 146,  24);
    tbsize_addbutton(&tbsize_results[4], 146,   2, 169,  24);
    tbsize_addbutton(&tbsize_results[4], 169,   2, 192,  24);

    tbsize_results[5] = init_tbsize_result(39, 0, 0, 672, 92, 882, 22);
    tbsize_addbutton(&tbsize_results[5],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[5],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[5],   0,   2,   8,  29);
    tbsize_addbutton(&tbsize_results[5],   0,  29,  23,  51);
    tbsize_addbutton(&tbsize_results[5],  23,  29,  46,  51);
    tbsize_addbutton(&tbsize_results[5],  46,  29,  69,  51);
    tbsize_addbutton(&tbsize_results[5],  69,  29,  92,  51);
    tbsize_addbutton(&tbsize_results[5],  92,  29, 115,  51);
    tbsize_addbutton(&tbsize_results[5], 115,  29, 138,  51);
    tbsize_addbutton(&tbsize_results[5], 138,  29, 161,  51);
    tbsize_addbutton(&tbsize_results[5], 161,  29, 184,  51);
    tbsize_addbutton(&tbsize_results[5], 184,  29, 207,  51);
    tbsize_addbutton(&tbsize_results[5], 207,  29, 230,  51);
    tbsize_addbutton(&tbsize_results[5], 230,  29, 253,  51);
    tbsize_addbutton(&tbsize_results[5], 253,  29, 276,  51);
    tbsize_addbutton(&tbsize_results[5], 276,  29, 299,  51);
    tbsize_addbutton(&tbsize_results[5], 299,  29, 322,  51);
    tbsize_addbutton(&tbsize_results[5], 322,  29, 345,  51);
    tbsize_addbutton(&tbsize_results[5], 345,  29, 368,  51);
    tbsize_addbutton(&tbsize_results[5], 368,  29, 391,  51);
    tbsize_addbutton(&tbsize_results[5], 391,  29, 414,  51);
    tbsize_addbutton(&tbsize_results[5], 414,  29, 437,  51);
    tbsize_addbutton(&tbsize_results[5], 437,  29, 460,  51);
    tbsize_addbutton(&tbsize_results[5], 460,  29, 483,  51);
    tbsize_addbutton(&tbsize_results[5], 483,  29, 506,  51);
    tbsize_addbutton(&tbsize_results[5], 506,  29, 529,  51);
    tbsize_addbutton(&tbsize_results[5], 529,  29, 552,  51);
    tbsize_addbutton(&tbsize_results[5], 552,  29, 575,  51);
    tbsize_addbutton(&tbsize_results[5], 575,  29, 598,  51);
    tbsize_addbutton(&tbsize_results[5], 598,  29, 621,  51);
    tbsize_addbutton(&tbsize_results[5], 621,  29, 644,  51);
    tbsize_addbutton(&tbsize_results[5], 644,  29, 667,  51);
    tbsize_addbutton(&tbsize_results[5],   0,  51,  23,  73);
    tbsize_addbutton(&tbsize_results[5],  23,  51,  46,  73);
    tbsize_addbutton(&tbsize_results[5],  46,  51,  69,  73);
    tbsize_addbutton(&tbsize_results[5],  69,  51,  92,  73);
    tbsize_addbutton(&tbsize_results[5],  92,  51, 115,  73);
    tbsize_addbutton(&tbsize_results[5], 115,  51, 138,  73);
    tbsize_addbutton(&tbsize_results[5], 138,  51, 161,  73);

    tbsize_results[6] = init_tbsize_result(7, 0, 0, 48, 226, 23, 140);
    tbsize_addbutton(&tbsize_results[6],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[6],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[6],  46,   2,  94,  24);
    tbsize_addbutton(&tbsize_results[6],  94,   2, 117,  24);
    tbsize_addbutton(&tbsize_results[6], 117,   2, 140,  24);
    tbsize_addbutton(&tbsize_results[6], 140,   2, 163,  24);
    tbsize_addbutton(&tbsize_results[6],   0,  24,  23,  46);

    tbsize_results[7] = init_tbsize_result(7, 0, 0, 92, 226, 23, 140);
    tbsize_addbutton(&tbsize_results[7],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[7],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[7],   0,  24,  92,  32);
    tbsize_addbutton(&tbsize_results[7],   0,  32,  23,  54);
    tbsize_addbutton(&tbsize_results[7],  23,  32,  46,  54);
    tbsize_addbutton(&tbsize_results[7],  46,  32,  69,  54);
    tbsize_addbutton(&tbsize_results[7],  69,  32,  92,  54);

    tbsize_results[8] = init_tbsize_result(7, 0, 0, 672, 26, 194, 30);
    tbsize_addbutton(&tbsize_results[8],   0,   2,  31,  32);
    tbsize_addbutton(&tbsize_results[8],  31,   2,  62,  32);
    tbsize_addbutton(&tbsize_results[8],  62,   2,  70,  32);
    tbsize_addbutton(&tbsize_results[8],  70,   2, 101,  32);
    tbsize_addbutton(&tbsize_results[8], 101,   2, 132,  32);
    tbsize_addbutton(&tbsize_results[8], 132,   2, 163,  32);
    tbsize_addbutton(&tbsize_results[8],   0,  32,  31,  62);

    tbsize_results[9] = init_tbsize_result(7, 0, 0, 672, 64, 194, 30);
    tbsize_addbutton(&tbsize_results[9],   0,   2,  31,  32);
    tbsize_addbutton(&tbsize_results[9],  31,   2,  62,  32);
    tbsize_addbutton(&tbsize_results[9],  62,   2,  70,  32);
    tbsize_addbutton(&tbsize_results[9],  70,   2, 101,  32);
    tbsize_addbutton(&tbsize_results[9], 101,   2, 132,  32);
    tbsize_addbutton(&tbsize_results[9], 132,   2, 163,  32);
    tbsize_addbutton(&tbsize_results[9],   0,  32,  31,  62);

    tbsize_results[10] = init_tbsize_result(7, 0, 0, 672, 64, 194, 30);
    tbsize_addbutton(&tbsize_results[10],   0,   0,  31,  30);
    tbsize_addbutton(&tbsize_results[10],  31,   0,  62,  30);
    tbsize_addbutton(&tbsize_results[10],  62,   0,  70,  30);
    tbsize_addbutton(&tbsize_results[10],  70,   0, 101,  30);
    tbsize_addbutton(&tbsize_results[10], 101,   0, 132,  30);
    tbsize_addbutton(&tbsize_results[10], 132,   0, 163,  30);
    tbsize_addbutton(&tbsize_results[10],   0,  30,  31,  60);

    tbsize_results[11] = init_tbsize_result(7, 0, 0, 124, 226, 31, 188);
    tbsize_addbutton(&tbsize_results[11],   0,    0,  31,  30);
    tbsize_addbutton(&tbsize_results[11],  31,    0,  62,  30);
    tbsize_addbutton(&tbsize_results[11],   0,   30, 124,  38);
    tbsize_addbutton(&tbsize_results[11],   0,   38,  31,  68);
    tbsize_addbutton(&tbsize_results[11],  31,   38,  62,  68);
    tbsize_addbutton(&tbsize_results[11],  62,   38,  93,  68);
    tbsize_addbutton(&tbsize_results[11],  93,   38, 124,  68);

    tbsize_results[12] = init_tbsize_result(7, 0, 0, 672, 26, 146, 22);
    tbsize_addbutton(&tbsize_results[12],   0,   2,  23,  24);
    tbsize_addbutton(&tbsize_results[12],  23,   2,  46,  24);
    tbsize_addbutton(&tbsize_results[12],  46,   2,  54,  24);
    tbsize_addbutton(&tbsize_results[12],  54,   2,  77,  24);
    tbsize_addbutton(&tbsize_results[12],  77,   2, 100,  24);
    tbsize_addbutton(&tbsize_results[12], 100,   2, 123,  24);
    tbsize_addbutton(&tbsize_results[12], 123,   2, 146,  24);

    tbsize_results[13] = init_tbsize_result(7, 0, 0, 672, 26, 146, 100);
    tbsize_addbutton(&tbsize_results[13],   0,   0,  23, 100);
    tbsize_addbutton(&tbsize_results[13],  23,   0,  46, 100);
    tbsize_addbutton(&tbsize_results[13],  46,   0,  54, 100);
    tbsize_addbutton(&tbsize_results[13],  54,   0,  77, 100);
    tbsize_addbutton(&tbsize_results[13],  77,   0, 100, 100);
    tbsize_addbutton(&tbsize_results[13], 100,   0, 123, 100);
    tbsize_addbutton(&tbsize_results[13], 123,   0, 146, 100);

    tbsize_results[14] = init_tbsize_result(10, 0, 0, 672, 26, 146, 100);
    tbsize_addbutton(&tbsize_results[14],   0,   0,  23, 100);
    tbsize_addbutton(&tbsize_results[14],  23,   0,  46, 100);
    tbsize_addbutton(&tbsize_results[14],  46,   0,  54, 100);
    tbsize_addbutton(&tbsize_results[14],  54,   0,  77, 100);
    tbsize_addbutton(&tbsize_results[14],  77,   0, 100, 100);
    tbsize_addbutton(&tbsize_results[14], 100,   0, 123, 100);
    tbsize_addbutton(&tbsize_results[14], 123,   0, 146, 100);
    tbsize_addbutton(&tbsize_results[14], 146,   0, 169, 100);
    tbsize_addbutton(&tbsize_results[14], 169,   0, 192, 100);
    tbsize_addbutton(&tbsize_results[14], 192,   0, 215, 100);

    tbsize_results[15] = init_tbsize_result(11, 0, 0, 672, 26, 238, 39);
    tbsize_addbutton(&tbsize_results[15],   0,   0,  23,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15],  23,   0,  46,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15],  46,   0,  54,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15],  54,   0,  77,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15],  77,   0, 100,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15], 100,   0, 123,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15], 123,   0, 146,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15], 146,   0, 169,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15], 169,   0, 192,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15], 192,   0, 215,  23 + fontheight);
    tbsize_addbutton(&tbsize_results[15], 215,   0, 238,  23 + fontheight);

    tbsize_results[16] = init_tbsize_result(11, 0, 0, 672, 26, 239, 22);
    tbsize_addbutton(&tbsize_results[16],   0,   0,  23,  22);
    tbsize_addbutton(&tbsize_results[16],  23,   0,  46,  22);
    tbsize_addbutton(&tbsize_results[16],  46,   0,  54,  22);
    tbsize_addbutton(&tbsize_results[16],  54,   0,  77,  22);
    tbsize_addbutton(&tbsize_results[16],  77,   0, 100,  22);
    tbsize_addbutton(&tbsize_results[16], 100,   0, 123,  22);
    tbsize_addbutton(&tbsize_results[16], 123,   0, 146,  22);
    tbsize_addbutton(&tbsize_results[16], 146,   0, 169,  22);
    tbsize_addbutton(&tbsize_results[16], 169,   0, 192,  22);
    tbsize_addbutton(&tbsize_results[16], 192,   0, 215,  22);
    tbsize_addbutton(&tbsize_results[16], 215,   0, 238,  22);

    buttonwidth = 7 + string_width(STRING1);

    tbsize_results[17] = init_tbsize_result(3, 0, 0, 672, 26, 489, 39);
    tbsize_addbutton(&tbsize_results[17],   0,   2, buttonwidth,  25 + fontheight);
    tbsize_addbutton(&tbsize_results[17], buttonwidth,   2, 2*buttonwidth + 4,  25 + fontheight);
    tbsize_addbutton(&tbsize_results[17], 2*buttonwidth + 4,   2, 3*buttonwidth + 4,  25 + fontheight);

    tbsize_results[18] = init_tbsize_result(6, 0, 0, 672, 104, 978, 24);
    tbsize_addbutton(&tbsize_results[18],   0,   2, buttonwidth,  10 + fontheight);
    tbsize_addbutton(&tbsize_results[18], buttonwidth,   2, 2*buttonwidth,  10 + fontheight);
    tbsize_addbutton(&tbsize_results[18], 2*buttonwidth,   2, 3*buttonwidth,  10 + fontheight);
    tbsize_addbutton(&tbsize_results[18], 3*buttonwidth,   2, 4*buttonwidth,  10 + fontheight);
    tbsize_addbutton(&tbsize_results[18], 4*buttonwidth,   2, 5*buttonwidth + 4,  10 + fontheight);
    tbsize_addbutton(&tbsize_results[18], 5*buttonwidth + 4,   2, 5*buttonwidth + 4 + string_width(STRING2) + 11,  10 + fontheight);

    tbsize_results[19] = init_tbsize_result(6, 0, 0, 672, 28, 978, 38);
    tbsize_addbutton(&tbsize_results[19],   0,   0, buttonwidth,  22 + fontheight);
    tbsize_addbutton(&tbsize_results[19], buttonwidth,   0, 2*buttonwidth,  22 + fontheight);
    tbsize_addbutton(&tbsize_results[19], 2*buttonwidth,   0, 3*buttonwidth,  22 + fontheight);
    tbsize_addbutton(&tbsize_results[19], 3*buttonwidth,   0, 4*buttonwidth,  22 + fontheight);
    tbsize_addbutton(&tbsize_results[19], 4*buttonwidth,   0, 5*buttonwidth + 4,  22 + fontheight);
    tbsize_addbutton(&tbsize_results[19], 5*buttonwidth + 4,   0, 5*buttonwidth + 4 + string_width(STRING2) + 11,  22 + fontheight);

    tbsize_results[20] = init_tbsize_result(3, 0, 0, 672, 100, 239, 102);
    tbsize_addbutton(&tbsize_results[20],   0,   2, 100, 102);
    tbsize_addbutton(&tbsize_results[20], 100,   2, 139, 102);
    tbsize_addbutton(&tbsize_results[20], 139,   2, 239, 102);

    tbsize_results[21] = init_tbsize_result(3, 0, 0, 672, 42, 185, 40);
    tbsize_addbutton(&tbsize_results[21],   0,   2,  75,  40);
    tbsize_addbutton(&tbsize_results[21],  75,   2, 118,  40);
    tbsize_addbutton(&tbsize_results[21], 118,   2, 165 + string_width(STRING2),  40);

    tbsize_results[22] = init_tbsize_result(1, 0, 0, 672, 42, 67, 40);
    tbsize_addbutton(&tbsize_results[22],   0,   2,  47 + string_width(STRING2),  40);

    tbsize_results[23] = init_tbsize_result(2, 0, 0, 672, 42, 67, 41);
    tbsize_addbutton(&tbsize_results[23],   0,   2, 672,  25 + fontheight);
    tbsize_addbutton(&tbsize_results[23],   0,  25 + fontheight, 672,  48 + 2*fontheight);

    tbsize_results[24] = init_tbsize_result(1, 0, 0, 672, 42, 67, 40);
    tbsize_addbutton(&tbsize_results[24],   0,   2,  11 + string_width(STRING2),  24);

    tbsize_results[25] = init_tbsize_result(1, 0, 0, 672, 42, 67, 40);
    tbsize_addbutton(&tbsize_results[25],   0,   2,  40,  24);

    tbsize_results[26] = init_tbsize_result(1, 0, 0, 672, 42, 67, 40);
    tbsize_addbutton(&tbsize_results[26],   0,   2,  40,  24);

    tbsize_results[27] = init_tbsize_result(1, 0, 0, 672, 42, 67, 40);
    tbsize_addbutton(&tbsize_results[27],   0,   2,  40,  24);
}