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
typedef  int /*<<< orphan*/  temp_path ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CreateFileW (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetTempFileNameW (char*,char const*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GetTempPathW (int,char*) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 

__attribute__((used)) static HANDLE create_temp_file(WCHAR *temp_file)
{
    HANDLE file = INVALID_HANDLE_VALUE;
    WCHAR temp_path[MAX_PATH];

    if (GetTempPathW(sizeof(temp_path) / sizeof(temp_path[0]), temp_path))
    {
        static const WCHAR img[] = { 'i','m','g',0 };

        if (GetTempFileNameW(temp_path, img, 0, temp_file))
            file = CreateFileW(temp_file, GENERIC_READ | GENERIC_WRITE, 0, NULL,
             CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    }
    return file;
}