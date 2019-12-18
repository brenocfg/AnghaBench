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
struct TYPE_3__ {int /*<<< orphan*/  kb_size; scalar_t__ value; } ;
typedef  TYPE_1__ StrFormatSizeResult ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 TYPE_1__* StrFormatSize_results ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pStrFormatKBSizeW (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (scalar_t__) ; 

__attribute__((used)) static void test_StrFormatKBSizeW(void)
{
  WCHAR szBuffW[256];
  char szBuff[256];
  const StrFormatSizeResult* result = StrFormatSize_results;

  if (!pStrFormatKBSizeW)
  {
    win_skip("StrFormatKBSizeW() is not available\n");
    return;
  }

  while(result->value)
  {
    pStrFormatKBSizeW(result->value, szBuffW, 256);
    WideCharToMultiByte(CP_ACP, 0, szBuffW, -1, szBuff, ARRAY_SIZE(szBuff), NULL, NULL);

    ok(!strcmp(result->kb_size, szBuff), "Formatted %s wrong: got %s, expected %s\n",
       wine_dbgstr_longlong(result->value), szBuff, result->kb_size);
    result++;
  }
}