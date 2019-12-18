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
typedef  char* LPSTR ;

/* Variables and functions */
 char* StrRChrA (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_StrRChrA(void)
{
  char string[129];
  WORD count;

  /* this test crashes on win2k SP4 */
  /*ok(!StrRChrA(NULL, NULL,'\0'), "found a character in a NULL string!\n");*/

  for (count = 32; count < 128; count++)
    string[count] = (char)count;
  string[128] = '\0';

  for (count = 32; count < 128; count++)
  {
    LPSTR result = StrRChrA(string+32, NULL, count);
    ok(result - string == count, "found char %d in wrong place\n", count);
  }

  for (count = 32; count < 128; count++)
  {
    LPSTR result = StrRChrA(string+count+1, NULL, count);
    ok(!result, "found char not in the string\n");
  }

  for (count = 32; count < 128; count++)
  {
    LPSTR result = StrRChrA(string+count+1, string + 127, count);
    ok(!result, "found char not in the string\n");
  }
}