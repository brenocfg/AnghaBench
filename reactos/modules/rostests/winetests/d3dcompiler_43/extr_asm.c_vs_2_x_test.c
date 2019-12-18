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
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; } ;
struct shader_test {char* member_0; TYPE_1__ member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct shader_test*) ; 
 int /*<<< orphan*/  exec_tests (char*,struct shader_test*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vs_2_x_test(void) {
    struct shader_test tests[] = {
        {   /* shader 0 */
            "vs_2_x\n"
            "rep i0\n"
            "break\n"
            "endrep\n",
            {0xfffe0201, 0x01000026, 0xf0e40000, 0x0000002c, 0x00000027, 0x0000ffff}
        },
        {   /* shader 1 */
            "vs_2_x\n"
            "if_ge r0, r1\n"
            "endif\n",
            {0xfffe0201, 0x02030029, 0x80e40000, 0x80e40001, 0x0000002b, 0x0000ffff}
        },
        {   /* shader 2 */
            "vs_2_x\n"
            "rep i0\n"
            "break_ne r0, r1\n"
            "endrep",
            {0xfffe0201, 0x01000026, 0xf0e40000, 0x0205002d, 0x80e40000, 0x80e40001,
             0x00000027, 0x0000ffff}
        },

        /* predicates */
        {   /* shader 3 */
            "vs_2_x\n"
            "setp_gt p0, r0, r1\n"
            "(!p0) add r2, r2, r3\n",
            {0xfffe0201, 0x0301005e, 0xb00f1000, 0x80e40000, 0x80e40001, 0x14000002,
             0x800f0002, 0xbde41000, 0x80e40002, 0x80e40003, 0x0000ffff}
        },
        {   /* shader 4 */
            "vs_2_x\n"
            "if p0.x\n"
            "else\n"
            "endif\n",
            {0xfffe0201, 0x01000028, 0xb0001000, 0x0000002a, 0x0000002b, 0x0000ffff}
        },
        {   /* shader 5 */
            "vs_2_x\n"
            "callnz l0, !p0.z\n"
            "ret\n"
            "label l0\n"
            "ret\n",
            {0xfffe0201, 0x0200001a, 0xa0e41000, 0xbdaa1000, 0x0000001c,
             0x0100001e, 0xa0e41000, 0x0000001c, 0x0000ffff}
        },
        {   /* shader 6 */
            "vs.2.x\n"
            "rep i0\n"
            "breakp p0.w\n"
            "endrep\n",
            {0xfffe0201, 0x01000026, 0xf0e40000, 0x01000060, 0xb0ff1000,
             0x00000027, 0x0000ffff}
        },
    };

    exec_tests("vs_2_x", tests, ARRAY_SIZE(tests));
}