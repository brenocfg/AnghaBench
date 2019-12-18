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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CONVERT_I8 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (double) ; 
 int /*<<< orphan*/  LONG64 ; 
 int /*<<< orphan*/  VarR8FromI8 ; 

__attribute__((used)) static void test_VarR8FromI8(void)
{
  CONVVARS(LONG64);

  CONVERT(VarR8FromI8, -1); EXPECT(-1.0);
  CONVERT(VarR8FromI8, 0);  EXPECT(0.0);
  CONVERT(VarR8FromI8, 1);  EXPECT(1.0);
#if defined(__i386__) && (defined(_MSC_VER) || defined(__GNUC__))
  CONVERT_I8(VarR8FromI8, 0x7fffffff,0xffffffff); EXPECT(9223372036854775808.0);
#endif
}