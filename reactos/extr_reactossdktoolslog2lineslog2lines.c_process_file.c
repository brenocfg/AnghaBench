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
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  l2l_dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 void* load_file (char const*,size_t*) ; 
 int process_data (void*,size_t,char*) ; 

__attribute__((used)) static int
process_file(const char *file_name, size_t offset, char *toString)
{
    void *FileData;
    size_t FileSize;
    int res = 1;

    FileData = load_file(file_name, &FileSize);
    if (!FileData)
    {
        l2l_dbg(0, "An error occured loading '%s'\n", file_name);
    }
    else
    {
        res = process_data(FileData, offset, toString);
        free(FileData);
    }
    return res;
}