#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int succeeded; struct TYPE_4__* next; int /*<<< orphan*/  result; int /*<<< orphan*/  testname; } ;
typedef  int /*<<< orphan*/  TEST_RESULT_INFO ;
typedef  TYPE_1__* PTEST_RESULT_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  close_file () ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ file_pointer ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_file (char*) ; 
 int /*<<< orphan*/  read_until (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_until_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_to_next_test () ; 
 int /*<<< orphan*/  skip_whitespace () ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* test_result_info_list ; 

__attribute__((used)) static void
parse_file(char *filename)
{
  PTEST_RESULT_INFO test_result_info;

  read_file(filename);

  do
    {
      if (!skip_to_next_test())
        {
          break;
        }

	  /*
	   * FORMAT:
	   * [ROSREGTEST:][space][|][<testname>][|][space][Status:][space][<result of running test>]
	   */

      test_result_info = malloc(sizeof(TEST_RESULT_INFO));
      if (test_result_info == NULL)
        {
	      printf("Out of memory\n");
	      exit(1);
        }

      /* Skip whitespaces */
      skip_whitespace();

  	  /* [|] */
      file_pointer++;

	  /* <testname> */
	  read_until(')', test_result_info->testname);

   	  /* [|] */
      file_pointer++;

	  /* [space] */
      file_pointer++;

  	  /* Status: */
      file_pointer += 7;

  	  /* [space] */
      file_pointer++;

  	  /* <result of running test> */
	  read_until_end(test_result_info->result);

	  if (strncmp(test_result_info->result, "Success", 7) == 0)
        {
	      test_result_info->succeeded = 1;
        }
      else
        {
          test_result_info->succeeded = 0;
        }

      test_result_info->next = test_result_info_list;
      test_result_info_list = test_result_info;
    } while (1);

  close_file();
}