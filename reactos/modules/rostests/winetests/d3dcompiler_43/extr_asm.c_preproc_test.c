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
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; } ;
struct shader_test {char* member_0; TYPE_1__ member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct shader_test*) ; 
 int /*<<< orphan*/  exec_tests (char*,struct shader_test*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void preproc_test(void) {
    struct shader_test tests[] = {
        {   /* shader 0 */
            "vs.1.1\r\n"
            "//some comments\r\n"
            "//other comments\n"
            "; yet another comment\r\n"
            "add r0, r0, r1\n",
            {0xfffe0101, 0x00000002, 0x800f0000, 0x80e40000, 0x80e40001, 0x0000ffff}
        },
        {   /* shader 1 */
            "#line 1 \"vertex.vsh\"\n"
            "vs.1.1\n",
            {0xfffe0101, 0x0000ffff}
        },
        {   /* shader 2 */
            "#define REG 1 + 2 +\\\n"
            "3 + 4\n"
            "vs.1.1\n"
            "mov r0, c0[ REG ]\n",
            {0xfffe0101, 0x00000001, 0x800f0000, 0xa0e4000a, 0x0000ffff}
        },
    };

    exec_tests("preproc", tests, ARRAY_SIZE(tests));
}