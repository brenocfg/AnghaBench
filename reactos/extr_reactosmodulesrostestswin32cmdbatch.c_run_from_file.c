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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  UnmapViewOfFile (char const*) ; 
 int /*<<< orphan*/  map_file (char const*,char const**) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_test (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static void run_from_file(const char *file_name)
{
    char out_name[MAX_PATH];
    const char *test_data, *out_data;
    DWORD test_size, out_size;

    test_size = map_file(file_name, &test_data);
    if(!test_size) {
        ok(0, "Could not map file %s: %u\n", file_name, GetLastError());
        return;
    }

    sprintf(out_name, "%s.exp", file_name);
    out_size = map_file(out_name, &out_data);
    if(!out_size) {
        ok(0, "Could not map file %s: %u\n", out_name, GetLastError());
        UnmapViewOfFile(test_data);
        return;
    }

    run_test(test_data, test_size, out_data, out_size);

    UnmapViewOfFile(test_data);
    UnmapViewOfFile(out_data);
}