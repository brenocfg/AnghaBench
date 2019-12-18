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
struct TYPE_3__ {int /*<<< orphan*/  kb_size; scalar_t__ value; int /*<<< orphan*/  kb_size2; scalar_t__ kb_size_broken; } ;
typedef  TYPE_1__ StrFormatSizeResult ;

/* Variables and functions */
 TYPE_1__* StrFormatSize_results ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pStrFormatKBSizeA (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (scalar_t__) ; 

__attribute__((used)) static void test_StrFormatKBSizeA(void)
{
  char szBuff[256];
  const StrFormatSizeResult* result = StrFormatSize_results;

  if (!pStrFormatKBSizeA)
  {
    win_skip("StrFormatKBSizeA() is not available\n");
    return;
  }

  while(result->value)
  {
    pStrFormatKBSizeA(result->value, szBuff, 256);

    /* shlwapi on Win98 SE does not appear to apply delimiters to the output
     * and does not correctly handle extremely large values. */
    ok(!strcmp(result->kb_size, szBuff) ||
      (result->kb_size_broken && !strcmp(result->kb_size2, szBuff)),
        "Formatted %s wrong: got %s, expected %s\n",
       wine_dbgstr_longlong(result->value), szBuff, result->kb_size);
    result++;
  }
}