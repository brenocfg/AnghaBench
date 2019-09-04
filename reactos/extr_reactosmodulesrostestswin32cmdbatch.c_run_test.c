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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnmapViewOfFile (char const*) ; 
 char* convert_input_data (char const*,scalar_t__,scalar_t__*) ; 
 scalar_t__ map_file (char*,char const**) ; 
 int /*<<< orphan*/  run_cmd (char const*,scalar_t__) ; 
 int /*<<< orphan*/  test_output (char const*,scalar_t__,char const*,scalar_t__) ; 

__attribute__((used)) static void run_test(const char *cmd_data, DWORD cmd_size, const char *exp_data, DWORD exp_size)
{
    const char *out_data, *actual_cmd_data;
    DWORD out_size, actual_cmd_size;

    actual_cmd_data = convert_input_data(cmd_data, cmd_size, &actual_cmd_size);
    if(!actual_cmd_size || !actual_cmd_data)
        goto cleanup;

    if(!run_cmd(actual_cmd_data, actual_cmd_size))
        goto cleanup;

    out_size = map_file("test.out", &out_data);
    if(out_size) {
        test_output(out_data, out_size, exp_data, exp_size);
        UnmapViewOfFile(out_data);
    }
    DeleteFileA("test.out");
    DeleteFileA("test.err");

cleanup:
    HeapFree(GetProcessHeap(), 0, (LPVOID)actual_cmd_data);
}