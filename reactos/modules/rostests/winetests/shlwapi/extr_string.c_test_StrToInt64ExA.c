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
struct TYPE_3__ {int str_to_int64_ex; int str_to_int64_hex; scalar_t__ string; } ;
typedef  TYPE_1__ StrToIntResult ;
typedef  int LONGLONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  STIF_SUPPORT_HEX ; 
 TYPE_1__* StrToInt_results ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pStrToInt64ExA (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int) ; 

__attribute__((used)) static void test_StrToInt64ExA(void)
{
  const StrToIntResult *result = StrToInt_results;
  LONGLONG return_val;
  BOOL bRet;

  if (!pStrToInt64ExA)
  {
    win_skip("StrToInt64ExA() is not available\n");
    return;
  }

  while (result->string)
  {
    return_val = -1;
    bRet = pStrToInt64ExA(result->string,0,&return_val);
    ok(!bRet || return_val != -1, "No result returned from '%s'\n",
       result->string);
    if (bRet)
      ok(return_val == result->str_to_int64_ex, "converted '%s' wrong (%s)\n",
         result->string, wine_dbgstr_longlong(return_val));
    result++;
  }

  result = StrToInt_results;
  while (result->string)
  {
    return_val = -1;
    bRet = pStrToInt64ExA(result->string,STIF_SUPPORT_HEX,&return_val);
    ok(!bRet || return_val != -1, "No result returned from '%s'\n",
       result->string);
    if (bRet)
      ok(return_val == result->str_to_int64_hex, "converted '%s' wrong (%s)\n",
         result->string, wine_dbgstr_longlong(return_val));
    result++;
  }
}