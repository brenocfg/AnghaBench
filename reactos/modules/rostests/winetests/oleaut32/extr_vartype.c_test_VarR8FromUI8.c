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
 int /*<<< orphan*/  CONVERT_I8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (double) ; 
 int /*<<< orphan*/  ULONG64 ; 
 int /*<<< orphan*/  VarR8FromUI8 ; 

__attribute__((used)) static void test_VarR8FromUI8(void)
{
  CONVVARS(ULONG64);

  CONVERT(VarR8FromUI8, 0); EXPECT(0.0);
  CONVERT(VarR8FromUI8, 1); EXPECT(1.0);
#if defined(__i386__) && (defined(_MSC_VER) || defined(__GNUC__))
  CONVERT_I8(VarR8FromUI8, 0x80000000,0); EXPECT(9223372036854775808.0);
#endif
}