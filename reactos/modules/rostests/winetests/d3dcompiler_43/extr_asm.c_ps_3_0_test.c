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
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; } ;
struct shader_test {char* member_0; TYPE_1__ member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct shader_test*) ; 
 int /*<<< orphan*/  exec_tests (char*,struct shader_test*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps_3_0_test(void) {
    struct shader_test tests[] = {
        {   /* shader 0 */
            "ps_3_0\n"
            "mov r0, c0\n",
            {0xffff0300, 0x02000001, 0x800f0000, 0xa0e40000, 0x0000ffff}
        },
        {   /* shader 1 */
            "ps_3_0\n"
            "dcl_normal5 v0\n",
            {0xffff0300, 0x0200001f, 0x80050003, 0x900f0000, 0x0000ffff}
        },
        {   /* shader 2 */
            "ps_3_0\n"
            "mov r0, vPos\n",
            {0xffff0300, 0x02000001, 0x800f0000, 0x90e41000, 0x0000ffff}
        },
        {   /* shader 3 */
            "ps_3_0\n"
            "mov r0, vFace\n",
            {0xffff0300, 0x02000001, 0x800f0000, 0x90e41001, 0x0000ffff}
        },
        {   /* shader 4 */
            "ps_3_0\n"
            "mov r0, v[ aL + 12 ]\n",
            {0xffff0300, 0x03000001, 0x800f0000, 0x90e4200c, 0xf0e40800, 0x0000ffff}
        },
        {   /* shader 5 */
            "ps_3_0\n"
            "loop aL, i0\n"
            "mov r0, v0[aL]\n"
            "endloop\n",
            {0xffff0300, 0x0200001b, 0xf0e40800, 0xf0e40000, 0x03000001, 0x800f0000,
             0x90e42000, 0xf0e40800, 0x0000001d, 0x0000ffff}
        },
        {   /* shader 6 */
            "ps_3_0\n"
            "texldl r0, v0, s0\n",
            {0xffff0300, 0x0300005f, 0x800f0000, 0x90e40000, 0xa0e40800, 0x0000ffff}
        },
        {   /* shader 7 */
            "ps_3_0\n"
            "add_pp r0, r0, r1\n",
            {0xffff0300, 0x03000002, 0x802f0000, 0x80e40000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 8 */
            "ps_3_0\n"
            "dsx_sat r0, r1\n",
            {0xffff0300, 0x0200005b, 0x801f0000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 9 */
            "ps_3_0\n"
            "texldd_pp r0, r1, r2, r3, r4\n",
            {0xffff0300, 0x0500005d, 0x802f0000, 0x80e40001, 0x80e40002, 0x80e40003,
             0x80e40004, 0x0000ffff}
        },
        {   /* shader 10 */
            "ps_3_0\n"
            "texkill v0\n",
            {0xffff0300, 0x01000041, 0x900f0000, 0x0000ffff}
        },
        {   /* shader 11 */
            "ps_3_0\n"
            "add oC3, r0, r1\n",
            {0xffff0300, 0x03000002, 0x800f0803, 0x80e40000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 12 */
            "ps_3_0\n"
            "dcl_texcoord0_centroid v0\n",
            {0xffff0300, 0x0200001f, 0x80000005, 0x904f0000, 0x0000ffff}
        },
        {   /* shader 13 */
            "ps_3_0\n"
            "dcl_2d_centroid s0\n",
            {0xffff0300, 0x0200001f, 0x90000000, 0xa04f0800, 0x0000ffff}
        },
        {   /* shader 14 */
            "ps.3.0\n"
            "dcl_2d_pp s0\n",
            {0xffff0300, 0x0200001f, 0x90000000, 0xa02f0800, 0x0000ffff}
        },
    };

    exec_tests("ps_3_0", tests, ARRAY_SIZE(tests));
}