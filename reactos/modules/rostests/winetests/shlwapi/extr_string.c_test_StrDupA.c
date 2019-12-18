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
struct TYPE_3__ {int /*<<< orphan*/ * byte_size_64; scalar_t__ value; } ;
typedef  TYPE_1__ StrFormatSizeResult ;
typedef  char* LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (char*) ; 
 char* StrDupA (int /*<<< orphan*/ *) ; 
 TYPE_1__* StrFormatSize_results ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_StrDupA(void)
{
  LPSTR lpszStr;
  const StrFormatSizeResult* result = StrFormatSize_results;

  while(result->value)
  {
    lpszStr = StrDupA(result->byte_size_64);

    ok(lpszStr != NULL, "Dup failed\n");
    if (lpszStr)
    {
      ok(!strcmp(result->byte_size_64, lpszStr), "Copied string wrong\n");
      LocalFree(lpszStr);
    }
    result++;
  }

  /* Later versions of shlwapi return NULL for this, but earlier versions
   * returned an empty string (as Wine does).
   */
  lpszStr = StrDupA(NULL);
  ok(lpszStr == NULL || *lpszStr == '\0', "NULL string returned %p\n", lpszStr);
  LocalFree(lpszStr);
}