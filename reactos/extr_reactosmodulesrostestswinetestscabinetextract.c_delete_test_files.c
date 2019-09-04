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
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 

__attribute__((used)) static void delete_test_files(void)
{
    DeleteFileA("a.txt");
    DeleteFileA("b.txt");
    DeleteFileA("testdir\\c.txt");
    DeleteFileA("testdir\\d.txt");
    RemoveDirectoryA("testdir");

    DeleteFileA("extract.cab");
}