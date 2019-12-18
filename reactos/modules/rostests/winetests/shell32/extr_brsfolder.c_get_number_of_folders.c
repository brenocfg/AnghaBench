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
struct TYPE_4__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAA ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileA (char*,TYPE_1__*) ; 
 scalar_t__ FindNextFileA (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  lstrcpynA (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_number_of_folders(LPCSTR path)
{
    int number_of_folders = 0;
    char path_search_string[MAX_PATH];
    WIN32_FIND_DATAA find_data;
    HANDLE find_handle;

    lstrcpynA(path_search_string, path, MAX_PATH - 1);
    strcat(path_search_string, "*");

    find_handle = FindFirstFileA(path_search_string, &find_data);
    if (find_handle == INVALID_HANDLE_VALUE)
        return -1;

    do
    {
        if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            strcmp(find_data.cFileName, ".") != 0 &&
            strcmp(find_data.cFileName, "..") != 0)
        {
            number_of_folders++;
        }
    }
    while (FindNextFileA(find_handle, &find_data) != 0);

    FindClose(find_handle);
    return number_of_folders;
}