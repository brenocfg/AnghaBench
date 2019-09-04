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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetFileAttributesA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 

__attribute__((used)) static int test_Mapfile_createtemp(HANDLE *handle)
{
    SetFileAttributesA(filename,FILE_ATTRIBUTE_NORMAL);
    DeleteFileA(filename);
    *handle = CreateFileA(filename, GENERIC_READ|GENERIC_WRITE, 0, 0,
                         CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (*handle != INVALID_HANDLE_VALUE) {

        return 1;
    }

    return 0;
}