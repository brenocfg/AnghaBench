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
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; } ;
struct shader_test {char* member_0; TYPE_1__ member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct shader_test*) ; 
 int /*<<< orphan*/  exec_tests (char*,struct shader_test*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vs_2_0_test(void) {
    struct shader_test tests[] = {
        /* Basic instruction tests */
        {   /* shader 0 */
            "vs_2_0\n"
            "mov r0, r1\n",
            {0xfffe0200, 0x02000001, 0x800f0000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 1 */
            "vs_2_0\n"
            "lrp r0, v0, c0, r1\n",
            {0xfffe0200, 0x04000012, 0x800f0000, 0x90e40000, 0xa0e40000, 0x80e40001,
             0x0000ffff}
        },
        {   /* shader 2 */
            "vs_2_0\n"
            "dp4 oPos, v0, c0\n",
            {0xfffe0200, 0x03000009, 0xc00f0000, 0x90e40000, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 3 */
            "vs_2_0\n"
            "mov r0, c0[a0.x]\n",
            {0xfffe0200, 0x03000001, 0x800f0000, 0xa0e42000, 0xb0000000, 0x0000ffff}
        },
        {   /* shader 4 */
            "vs_2_0\n"
            "mov r0, c0[a0.y]\n",
            {0xfffe0200, 0x03000001, 0x800f0000, 0xa0e42000, 0xb0550000, 0x0000ffff}
        },
        {   /* shader 5 */
            "vs_2_0\n"
            "mov r0, c0[a0.z]\n",
            {0xfffe0200, 0x03000001, 0x800f0000, 0xa0e42000, 0xb0aa0000, 0x0000ffff}
        },
        {   /* shader 6 */
            "vs_2_0\n"
            "mov r0, c0[a0.w]\n",
            {0xfffe0200, 0x03000001, 0x800f0000, 0xa0e42000, 0xb0ff0000, 0x0000ffff}
        },
        {   /* shader 7 */
            "vs_2_0\n"
            "mov r0, c0[a0.w].x\n",
            {0xfffe0200, 0x03000001, 0x800f0000, 0xa0002000, 0xb0ff0000, 0x0000ffff}
        },
        {   /* shader 8 */
            "vs_2_0\n"
            "mov r0, -c0[a0.w+5].x\n",
            {0xfffe0200, 0x03000001, 0x800f0000, 0xa1002005, 0xb0ff0000, 0x0000ffff}
        },
        {   /* shader 9 */
            "vs_2_0\n"
            "mov r0, c0[a0]\n",
            {0xfffe0200, 0x03000001, 0x800f0000, 0xa0e42000, 0xb0e40000, 0x0000ffff}
        },
        {   /* shader 10 */
            "vs_2_0\n"
            "mov r0, c0[a0.xyww]\n",
            {0xfffe0200, 0x03000001, 0x800f0000, 0xa0e42000, 0xb0f40000, 0x0000ffff}
        },
        {   /* shader 11 */
            "vs_2_0\n"
            "add r0, c0[a0.x], c1[a0.y]\n", /* validation would fail on this line */
            {0xfffe0200, 0x05000002, 0x800f0000, 0xa0e42000, 0xb0000000, 0xa0e42001,
             0xb0550000, 0x0000ffff}
        },
        {   /* shader 12 */
            "vs_2_0\n"
            "rep i0\n"
            "endrep\n",
            {0xfffe0200, 0x01000026, 0xf0e40000, 0x00000027, 0x0000ffff}
        },
        {   /* shader 13 */
            "vs_2_0\n"
            "if b0\n"
            "else\n"
            "endif\n",
            {0xfffe0200, 0x01000028, 0xe0e40800, 0x0000002a, 0x0000002b, 0x0000ffff}
        },
        {   /* shader 14 */
            "vs_2_0\n"
            "loop aL, i0\n"
            "endloop\n",
            {0xfffe0200, 0x0200001b, 0xf0e40800, 0xf0e40000, 0x0000001d, 0x0000ffff}
        },
        {   /* shader 15 */
            "vs_2_0\n"
            "nrm r0, c0\n",
            {0xfffe0200, 0x02000024, 0x800f0000, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 16 */
            "vs_2_0\n"
            "crs r0, r1, r2\n",
            {0xfffe0200, 0x03000021, 0x800f0000, 0x80e40001, 0x80e40002, 0x0000ffff}
        },
        {   /* shader 17 */
            "vs_2_0\n"
            "sgn r0, r1, r2, r3\n",
            {0xfffe0200, 0x04000022, 0x800f0000, 0x80e40001, 0x80e40002, 0x80e40003,
             0x0000ffff}
        },
        {   /* shader 18 */
            "vs_2_0\n"
            "sincos r0, r1, r2, r3\n",
            {0xfffe0200, 0x04000025, 0x800f0000, 0x80e40001, 0x80e40002, 0x80e40003,
             0x0000ffff}
        },
        {   /* shader 19 */
            "vs_2_0\n"
            "pow r0, r1, r2\n",
            {0xfffe0200, 0x03000020, 0x800f0000, 0x80e40001, 0x80e40002, 0x0000ffff}
        },
        {   /* shader 20 */
            "vs_2_0\n"
            "mova a0.y, c0.z\n",
            {0xfffe0200, 0x0200002e, 0xb0020000, 0xa0aa0000, 0x0000ffff}
        },
        {   /* shader 21 */
            "vs_2_0\n"
            "defb b0, true\n"
            "defb b1, false\n",
            {0xfffe0200, 0x0200002f, 0xe00f0800, 0x00000001, 0x0200002f, 0xe00f0801,
             0x00000000, 0x0000ffff}
        },
        {   /* shader 22 */
            "vs_2_0\n"
            "defi i0, -1, 1, 10, 0\n"
            "defi i1, 0, 40, 30, 10\n",
            {0xfffe0200, 0x05000030, 0xf00f0000, 0xffffffff, 0x00000001, 0x0000000a,
             0x00000000, 0x05000030, 0xf00f0001, 0x00000000, 0x00000028, 0x0000001e,
             0x0000000a, 0x0000ffff}
        },
        {   /* shader 23 */
            "vs_2_0\n"
            "loop aL, i0\n"
            "mov r0, c0[aL]\n"
            "endloop\n",
            {0xfffe0200, 0x0200001b, 0xf0e40800, 0xf0e40000, 0x03000001, 0x800f0000,
             0xa0e42000, 0xf0e40800, 0x0000001d, 0x0000ffff}
        },
        {   /* shader 24 */
            "vs_2_0\n"
            "call l0\n"
            "ret\n"
            "label l0\n"
            "ret\n",
            {0xfffe0200, 0x01000019, 0xa0e41000, 0x0000001c, 0x0100001e, 0xa0e41000,
             0x0000001c, 0x0000ffff}
        },
        {   /* shader 25 */
            "vs_2_0\n"
            "callnz l0, b0\n"
            "ret\n"
            "label l0\n"
            "ret\n",
            {0xfffe0200, 0x0200001a, 0xa0e41000, 0xe0e40800, 0x0000001c, 0x0100001e,
             0xa0e41000, 0x0000001c, 0x0000ffff}
        },
        {   /* shader 26 */
            "vs_2_0\n"
            "callnz l0, !b0\n"
            "ret\n"
            "label l0\n"
            "ret\n",
            {0xfffe0200, 0x0200001a, 0xa0e41000, 0xede40800, 0x0000001c, 0x0100001e,
             0xa0e41000, 0x0000001c, 0x0000ffff}
        },
        {   /* shader 27 */
            "vs_2_0\n"
            "if !b0\n"
            "else\n"
            "endif\n",
            {0xfffe0200, 0x01000028, 0xede40800, 0x0000002a, 0x0000002b, 0x0000ffff}
        },
        {   /* shader 28 */
            "vs_2_0\n"
            "call l3\n"
            "ret\n"
            "label l3\n"
            "ret\n",
            {0xfffe0200, 0x01000019, 0xa0e41003, 0x0000001c, 0x0100001e, 0xa0e41003, 0x0000001c, 0x0000ffff}
        },
        {   /* shader 29: labels up to 2047 are accepted even in vs_2_0 */
            "vs.2.0\n"
            "call l2047\n",
            {0xfffe0200, 0x01000019, 0xa0e417ff, 0x0000ffff}
        },
    };

    exec_tests("vs_2_0", tests, ARRAY_SIZE(tests));
}