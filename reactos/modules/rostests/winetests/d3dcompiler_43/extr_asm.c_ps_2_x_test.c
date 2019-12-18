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

__attribute__((used)) static void ps_2_x_test(void) {
    struct shader_test tests[] = {
        /* defb and defi are not supposed to work in ps_2_0 (even if defb actually works in ps_2_0 with native) */
        {   /* shader 0 */
            "ps_2_x\n"
            "defb b0, true\n"
            "defb b1, false\n",
            {0xffff0201, 0x0200002f, 0xe00f0800, 0x00000001, 0x0200002f, 0xe00f0801,
             0x00000000, 0x0000ffff}
        },
        {   /* shader 1 */
            "ps_2_x\n"
            "defi i0, -1, 1, 10, 0\n"
            "defi i1, 0, 40, 30, 10\n",
            {0xffff0201, 0x05000030, 0xf00f0000, 0xffffffff, 0x00000001, 0x0000000a,
             0x00000000, 0x05000030, 0xf00f0001, 0x00000000, 0x00000028, 0x0000001e,
             0x0000000a, 0x0000ffff}
        },
        {   /* shader 2 */
            "ps_2_x\n"
            "dsx r0, r0\n",
            {0xffff0201, 0x0200005b, 0x800f0000, 0x80e40000, 0x0000ffff}
        },
        {   /* shader 3 */
            "ps_2_x\n"
            "dsy r0, r0\n",
            {0xffff0201, 0x0200005c, 0x800f0000, 0x80e40000, 0x0000ffff}
        },
        {   /* shader 4 */
            "ps_2_x\n"
            "dcl_2d s2\n"
            "texldd r0, v1, s2, r3, r4\n",
            {0xffff0201, 0x0200001f, 0x90000000, 0xa00f0802, 0x0500005d, 0x800f0000,
             0x90e40001, 0xa0e40802, 0x80e40003, 0x80e40004, 0x0000ffff}
        },
        /* Static flow control tests */
        {   /* shader 5 */
            "ps_2_x\n"
            "call l0\n"
            "ret\n"
            "label l0\n"
            "ret\n",
            {0xffff0201, 0x01000019, 0xa0e41000, 0x0000001c, 0x0100001e, 0xa0e41000,
             0x0000001c, 0x0000ffff}
        },
        {   /* shader 6 */
            "ps_2_x\n"
            "callnz l0, b0\n"
            "ret\n"
            "label l0\n"
            "ret\n",
            {0xffff0201, 0x0200001a, 0xa0e41000, 0xe0e40800, 0x0000001c, 0x0100001e,
             0xa0e41000, 0x0000001c, 0x0000ffff}
        },
        {   /* shader 7 */
            "ps_2_x\n"
            "callnz l0, !b0\n"
            "ret\n"
            "label l0\n"
            "ret\n",
            {0xffff0201, 0x0200001a, 0xa0e41000, 0xede40800, 0x0000001c, 0x0100001e,
             0xa0e41000, 0x0000001c, 0x0000ffff}
        },
        {   /* shader 8 */
            "ps_2_x\n"
            "if !b0\n"
            "else\n"
            "endif\n",
            {0xffff0201, 0x01000028, 0xede40800, 0x0000002a, 0x0000002b, 0x0000ffff}
        },
        /* Dynamic flow control tests */
        {   /* shader 9 */
            "ps_2_x\n"
            "rep i0\n"
            "break\n"
            "endrep\n",
            {0xffff0201, 0x01000026, 0xf0e40000, 0x0000002c, 0x00000027, 0x0000ffff}
        },
        {   /* shader 10 */
            "ps_2_x\n"
            "if_ge r0, r1\n"
            "endif\n",
            {0xffff0201, 0x02030029, 0x80e40000, 0x80e40001, 0x0000002b, 0x0000ffff}
        },
        {   /* shader 11 */
            "ps_2_x\n"
            "rep i0\n"
            "break_ne r0, r1\n"
            "endrep",
            {0xffff0201, 0x01000026, 0xf0e40000, 0x0205002d, 0x80e40000, 0x80e40001,
             0x00000027, 0x0000ffff}
        },
        /* Predicates */
        {   /* shader 12 */
            "ps_2_x\n"
            "setp_gt p0, r0, r1\n"
            "(!p0) add r2, r2, r3\n",
            {0xffff0201, 0x0301005e, 0xb00f1000, 0x80e40000, 0x80e40001, 0x14000002,
             0x800f0002, 0xbde41000, 0x80e40002, 0x80e40003, 0x0000ffff}
        },
        {   /* shader 13 */
            "ps_2_x\n"
            "if p0.x\n"
            "else\n"
            "endif\n",
            {0xffff0201, 0x01000028, 0xb0001000, 0x0000002a, 0x0000002b, 0x0000ffff}
        },
        {   /* shader 14 */
            "ps_2_x\n"
            "callnz l0, !p0.z\n"
            "ret\n"
            "label l0\n"
            "ret\n",
            {0xffff0201, 0x0200001a, 0xa0e41000, 0xbdaa1000, 0x0000001c,
             0x0100001e, 0xa0e41000, 0x0000001c, 0x0000ffff}
        },
        {   /* shader 15 */
            "ps_2_x\n"
            "rep i0\n"
            "breakp p0.w\n"
            "endrep\n",
            {0xffff0201, 0x01000026, 0xf0e40000, 0x01000060, 0xb0ff1000,
             0x00000027, 0x0000ffff}
        },
        {   /* shader 16 */
            "ps.2.x\n"
            "call l2047\n"
            "ret\n"
            "label l2047\n"
            "ret\n",
            {0xffff0201, 0x01000019, 0xa0e417ff, 0x0000001c, 0x0100001e, 0xa0e417ff,
             0x0000001c, 0x0000ffff}
        },
    };

    exec_tests("ps_2_x", tests, ARRAY_SIZE(tests));
}