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
typedef  int WORD ;
typedef  char WCHAR ;
typedef  char* LPWSTR ;

/* Variables and functions */
 char* StrChrW (char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_StrChrW(void)
{
  WCHAR string[16385];
  WORD count;

  /* this test crashes on win2k SP4 */
  /*ok(!StrChrW(NULL,'\0'), "found a character in a NULL string!\n");*/

  for (count = 32; count < 16384; count++)
    string[count] = count;
  string[16384] = '\0';

  for (count = 32; count < 16384; count++)
  {
    LPWSTR result = StrChrW(string+32, count);
    ok((result - string) == count, "found char %d in wrong place\n", count);
  }

  for (count = 32; count < 16384; count++)
  {
    LPWSTR result = StrChrW(string+count+1, count);
    ok(!result, "found char not in the string\n");
  }
}