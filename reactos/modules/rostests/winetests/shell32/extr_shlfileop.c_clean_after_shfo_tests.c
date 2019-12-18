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

__attribute__((used)) static void clean_after_shfo_tests(void)
{
    DeleteFileA("test1.txt");
    DeleteFileA("test2.txt");
    DeleteFileA("test3.txt");
    DeleteFileA("test_5.txt");
    DeleteFileA("one.txt");
    DeleteFileA("test4.txt\\test1.txt");
    DeleteFileA("test4.txt\\test2.txt");
    DeleteFileA("test4.txt\\test3.txt");
    DeleteFileA("test4.txt\\one.txt");
    DeleteFileA("test4.txt\\nested\\two.txt");
    RemoveDirectoryA("test4.txt\\nested");
    RemoveDirectoryA("test4.txt");
    DeleteFileA("testdir2\\one.txt");
    DeleteFileA("testdir2\\test1.txt");
    DeleteFileA("testdir2\\test2.txt");
    DeleteFileA("testdir2\\test3.txt");
    DeleteFileA("testdir2\\test4.txt\\test1.txt");
    DeleteFileA("testdir2\\nested\\two.txt");
    RemoveDirectoryA("testdir2\\test4.txt");
    RemoveDirectoryA("testdir2\\nested");
    RemoveDirectoryA("testdir2");
    RemoveDirectoryA("c:\\testdir3");
    DeleteFileA("nonexistent\\notreal\\test2.txt");
    RemoveDirectoryA("nonexistent\\notreal");
    RemoveDirectoryA("nonexistent");
}