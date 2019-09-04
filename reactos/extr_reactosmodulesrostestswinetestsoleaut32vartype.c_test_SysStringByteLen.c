#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwLen; } ;
typedef  TYPE_1__ INTERNAL_BSTR ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetBSTR (TYPE_1__*) ; 
 int SysStringByteLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_SysStringByteLen(void)
{
  INTERNAL_BSTR bstr;
  BSTR str = GetBSTR(&bstr);

  bstr.dwLen = 0;
  ok (SysStringByteLen(str) == 0, "Expected dwLen 0, got %d\n", SysStringByteLen(str));
  bstr.dwLen = 2;
  ok (SysStringByteLen(str) == 2, "Expected dwLen 2, got %d\n", SysStringByteLen(str));
}