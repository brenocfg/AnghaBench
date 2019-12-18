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
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct shader_test {char* member_0; TYPE_1__ member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct shader_test*) ; 
 int /*<<< orphan*/  exec_tests (char*,struct shader_test*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vs_1_1_test(void) {
    struct shader_test tests[] = {
        /* Basic instruction tests */
        {   /* shader 0 */
            "vs_1_1\n"
            "add r0, r1, r2\n",
            {0xfffe0101, 0x00000002, 0x800f0000, 0x80e40001, 0x80e40002, 0x0000ffff}
        },
        {   /* shader 1 */
            "vs_1_1\n"
            "nop\n",
            {0xfffe0101, 0x00000000, 0x0000ffff}
        },
        /* Output register tests */
        {   /* shader 2 */
            "vs_1_1\n"
            "mov oPos, c0\n",
            {0xfffe0101, 0x00000001, 0xc00f0000, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 3 */
            "vs_1_1\n"
            "mov oT0, c0\n",
            {0xfffe0101, 0x00000001, 0xe00f0000, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 4 */
            "vs_1_1\n"
            "mov oT5, c0\n",
            {0xfffe0101, 0x00000001, 0xe00f0005, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 5 */
            "vs_1_1\n"
            "mov oD0, c0\n",
            {0xfffe0101, 0x00000001, 0xd00f0000, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 6 */
            "vs_1_1\n"
            "mov oD1, c0\n",
            {0xfffe0101, 0x00000001, 0xd00f0001, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 7 */
            "vs_1_1\n"
            "mov oFog, c0.x\n",
            {0xfffe0101, 0x00000001, 0xc00f0001, 0xa0000000, 0x0000ffff}
        },
        {   /* shader 8 */
            "vs_1_1\n"
            "mov oPts, c0.x\n",
            {0xfffe0101, 0x00000001, 0xc00f0002, 0xa0000000, 0x0000ffff}
        },
        /* A bunch of tests for declarations */
        {   /* shader 9 */
            "vs_1_1\n"
            "dcl_position0 v0",
            {0xfffe0101, 0x0000001f, 0x80000000, 0x900f0000, 0x0000ffff}
        },
        {   /* shader 10 */
            "vs_1_1\n"
            "dcl_position v1",
            {0xfffe0101, 0x0000001f, 0x80000000, 0x900f0001, 0x0000ffff}
        },
        {   /* shader 11 */
            "vs_1_1\n"
            "dcl_normal12 v15",
            {0xfffe0101, 0x0000001f, 0x800c0003, 0x900f000f, 0x0000ffff}
        },
        {   /* shader 12 */
            "vs_1_1\n"
            "add r0, v0, v1\n",
            {0xfffe0101, 0x00000002, 0x800f0000, 0x90e40000, 0x90e40001, 0x0000ffff}
        },
        {   /* shader 13 */
            "vs_1_1\n"
            "def c12, 0, -1, -0.5, 1024\n",
            {0xfffe0101, 0x00000051, 0xa00f000c, 0x00000000, 0xbf800000, 0xbf000000,
             0x44800000, 0x0000ffff}
        },
        {   /* shader 14: writemasks, swizzles */
            "vs_1_1\n"
            "dp4 r0.xw, r1.wzyx, r2.xxww\n",
            {0xfffe0101, 0x00000009, 0x80090000, 0x801b0001, 0x80f00002, 0x0000ffff}
        },
        {   /* shader 15: negation input modifier. Other modifiers not supprted in vs_1_1 */
            "vs_1_1\n"
            "add r0, -r0.x, -r1\n",
            {0xfffe0101, 0x00000002, 0x800f0000, 0x81000000, 0x81e40001, 0x0000ffff}
        },
        {   /* shader 16: relative addressing */
            "vs_1_1\n"
            "mov r0, c0[a0.x]\n",
            {0xfffe0101, 0x00000001, 0x800f0000, 0xa0e42000, 0x0000ffff}
        },
        {   /* shader 17: relative addressing */
            "vs_1_1\n"
            "mov r0, c1[a0.x + 2]\n",
            {0xfffe0101, 0x00000001, 0x800f0000, 0xa0e42003, 0x0000ffff}
        },
        {   /* shader 18 */
            "vs_1_1\n"
            "def c0, 1.0f, 1.0f, 1.0f, 0.5f\n",
            {0xfffe0101, 0x00000051, 0xa00f0000, 0x3f800000, 0x3f800000, 0x3f800000,
             0x3f000000, 0x0000ffff}
        },
        /* Other relative addressing tests */
        {   /* shader 19 */
            "vs_1_1\n"
            "mov r0, c[ a0.x + 12 ]\n",
            {0xfffe0101, 0x00000001, 0x800f0000, 0xa0e4200c, 0x0000ffff}
        },
        {   /* shader 20 */
            "vs_1_1\n"
            "mov r0, c[ 2 + a0.x ]\n",
            {0xfffe0101, 0x00000001, 0x800f0000, 0xa0e42002, 0x0000ffff}
        },
        {   /* shader 21 */
            "vs_1_1\n"
            "mov r0, c[ 2 + a0.x + 12 ]\n",
            {0xfffe0101, 0x00000001, 0x800f0000, 0xa0e4200e, 0x0000ffff}
        },
        {   /* shader 22 */
            "vs_1_1\n"
            "mov r0, c[ 2 + 10 + 12 ]\n",
            {0xfffe0101, 0x00000001, 0x800f0000, 0xa0e40018, 0x0000ffff}
        },
        {   /* shader 23 */
            "vs_1_1\n"
            "mov r0, c4[ 2 ]\n",
            {0xfffe0101, 0x00000001, 0x800f0000, 0xa0e40006, 0x0000ffff}
        },
        {   /* shader 24 */
            "vs_1_1\n"
            "rcp r0, v0.x\n",
            {0xfffe0101, 0x00000006, 0x800f0000, 0x90000000, 0x0000ffff}
        },
        {   /* shader 25 */
            "vs.1.1\n"
            "rsq r0, v0.x\n",
            {0xfffe0101, 0x00000007, 0x800f0000, 0x90000000, 0x0000ffff}
        },
    };

    exec_tests("vs_1_1", tests, ARRAY_SIZE(tests));
}