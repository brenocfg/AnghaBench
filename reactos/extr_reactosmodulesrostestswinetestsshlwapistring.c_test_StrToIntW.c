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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int str_to_int; scalar_t__ string; } ;
typedef  TYPE_1__ StrToIntResult ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int StrToIntW (int /*<<< orphan*/ *) ; 
 TYPE_1__* StrToInt_results ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int) ; 

__attribute__((used)) static void test_StrToIntW(void)
{
  WCHAR szBuff[256];
  const StrToIntResult *result = StrToInt_results;
  int return_val;

  while (result->string)
  {
    MultiByteToWideChar(CP_ACP, 0, result->string, -1, szBuff, ARRAY_SIZE(szBuff));
    return_val = StrToIntW(szBuff);
    ok(return_val == result->str_to_int, "converted '%s' wrong (%d)\n",
       result->string, return_val);
    result++;
  }
}