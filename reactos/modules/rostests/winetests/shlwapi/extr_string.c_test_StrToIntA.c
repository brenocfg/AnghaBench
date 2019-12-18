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
struct TYPE_3__ {int str_to_int; scalar_t__ string; } ;
typedef  TYPE_1__ StrToIntResult ;

/* Variables and functions */
 int StrToIntA (scalar_t__) ; 
 TYPE_1__* StrToInt_results ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int) ; 

__attribute__((used)) static void test_StrToIntA(void)
{
  const StrToIntResult *result = StrToInt_results;
  int return_val;

  while (result->string)
  {
    return_val = StrToIntA(result->string);
    ok(return_val == result->str_to_int, "converted '%s' wrong (%d)\n",
       result->string, return_val);
    result++;
  }
}