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

__attribute__((used)) static void ps_1_1_test(void) {
    struct shader_test tests[] = {
        {   /* shader 0 */
            "ps.1.1\r\n"
            "tex t0\r\n"
            "add r0.rgb, r0, r1\r\n"
            "+mov r0.a, t0\r\n",
            {0xffff0101, 0x00000042, 0xb00f0000, 0x00000002, 0x80070000, 0x80e40000,
             0x80e40001, 0x40000001, 0x80080000, 0xb0e40000, 0x0000ffff}
        },
        {   /* shader 1 */
            "ps.1.1\n"
            "mov_d4 r0, r1\n",
            {0xffff0101, 0x00000001, 0x8e0f0000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 2 */
            "ps_1_1\n"
            "def c2, 0, 0., 0, 0.\n",
            {0xffff0101, 0x00000051, 0xa00f0002, 0x00000000, 0x00000000, 0x00000000,
             0x00000000, 0x0000ffff}
        },
    };

    exec_tests("ps_1_1", tests, ARRAY_SIZE(tests));
}