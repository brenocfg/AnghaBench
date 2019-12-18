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

__attribute__((used)) static void vs_3_0_test(void) {
    struct shader_test tests[] = {
        {   /* shader 0 */
            "vs_3_0\n"
            "mov r0, c0\n",
            {0xfffe0300, 0x02000001, 0x800f0000, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 1 */
            "vs_3_0\n"
            "dcl_2d s0\n",
            {0xfffe0300, 0x0200001f, 0x90000000, 0xa00f0800, 0x0000ffff}
        },
        {   /* shader 2 */
            "vs_3_0\n"
            "dcl_position o0\n",
            {0xfffe0300, 0x0200001f, 0x80000000, 0xe00f0000, 0x0000ffff}
        },
        {   /* shader 3 */
            "vs_3_0\n"
            "dcl_texcoord12 o11\n",
            {0xfffe0300, 0x0200001f, 0x800c0005, 0xe00f000b, 0x0000ffff}
        },
        {   /* shader 4 */
            "vs_3_0\n"
            "texldl r0, v0, s0\n",
            {0xfffe0300, 0x0300005f, 0x800f0000, 0x90e40000, 0xa0e40800, 0x0000ffff}
        },
        {   /* shader 5 */
            "vs_3_0\n"
            "mov r0, c0[aL]\n",
            {0xfffe0300, 0x03000001, 0x800f0000, 0xa0e42000, 0xf0e40800, 0x0000ffff}
        },
        {   /* shader 6 */
            "vs_3_0\n"
            "mov o[ a0.x + 12 ], r0\n",
            {0xfffe0300, 0x03000001, 0xe00f200c, 0xb0000000, 0x80e40000, 0x0000ffff}
        },
        {   /* shader 7 */
            "vs_3_0\n"
            "add_sat r0, r0, r1\n",
            {0xfffe0300, 0x03000002, 0x801f0000, 0x80e40000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 8 */
            "vs_3_0\n"
            "mov r2, r1_abs\n",
            {0xfffe0300, 0x02000001, 0x800f0002, 0x8be40001, 0x0000ffff}
        },
        {   /* shader 9 */
            "vs_3_0\n"
            "mov r2, r1.xygb\n",
            {0xfffe0300, 0x02000001, 0x800f0002, 0x80940001, 0x0000ffff}
        },
        {   /* shader 10 */
            "vs_3_0\n"
            "mov r2.xyb, r1\n",
            {0xfffe0300, 0x02000001, 0x80070002, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 11 */
            "vs_3_0\n"
            "mova_sat a0.x, r1\n",
            {0xfffe0300, 0x0200002e, 0xb0110000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 12 */
            "vs_3_0\n"
            "sincos r0, r1\n",
            {0xfffe0300, 0x02000025, 0x800f0000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 13 */
            "vs_3_0\n"
            "def c0, 1.0f, 1.0f, 1.0f, 0.5f\n",
            {0xfffe0300, 0x05000051, 0xa00f0000, 0x3f800000, 0x3f800000, 0x3f800000,
             0x3f000000, 0x0000ffff}
        },
        {   /* shader 14: no register number checks with relative addressing */
            "vs.3.0\n"
            "add r0, v20[aL], r2\n",
            {0xfffe0300, 0x04000002, 0x800f0000, 0x90e42014, 0xf0e40800, 0x80e40002,
             0x0000ffff}
        },

    };

    exec_tests("vs_3_0", tests, ARRAY_SIZE(tests));
}