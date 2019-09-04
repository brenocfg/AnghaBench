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

/* Variables and functions */
 int /*<<< orphan*/  TEST_B1_FILE_SIZE ; 
 int /*<<< orphan*/  TEST_B2_FILE_SIZE ; 
 int /*<<< orphan*/  TEST_B3_FILE_SIZE ; 
 int /*<<< orphan*/  TEST_B4_FILE_SIZE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dos_data ; 
 int /*<<< orphan*/  nix_data ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int test_binary_fileio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int test_console_getchar () ; 
 int test_console_io () ; 
 int test_console_putch () ; 
 scalar_t__ test_file_truncate (int /*<<< orphan*/ ) ; 
 int test_text_fileio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int test_unlink_files () ; 

__attribute__((used)) static int test_files(int test_num, char* type)
{
    int result = 0;

    printf("performing test: %d (%s)\n", test_num, type);


    if (test_file_truncate(_T("zerosize.foo"))) {
        printf("System unable to truncate files yet, unlinking:\n");
        test_unlink_files();
    }

    switch (test_num) {
    case 1:
        result = test_text_fileio(_T("text.dos"), dos_data, 166, TEST_B1_FILE_SIZE);
        break;
    case 2:
        result = test_binary_fileio(_T("binary.dos"), dos_data, TEST_B2_FILE_SIZE, 166);
        break;
    case 3:
        result = test_text_fileio(_T("text.nix"), nix_data, 162, TEST_B3_FILE_SIZE);
        break;
    case 4:
        result = test_binary_fileio(_T("binary.nix"), nix_data, TEST_B4_FILE_SIZE, 162);
        break;
    case 5:
        result = test_console_io();
        break;
    case 6:
        result = test_console_getchar();
        break;
    case 7:
        result = test_console_putch();
        break;
    case -1:
        result = test_unlink_files();
        break;
    default:
        _tprintf(_T("no test number selected\n"));
        break;
    }
    return result;
}