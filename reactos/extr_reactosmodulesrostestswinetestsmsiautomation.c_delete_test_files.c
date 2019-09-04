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
 char* msifile ; 

__attribute__((used)) static void delete_test_files(void)
{
    DeleteFileA(msifile);
    DeleteFileA("msitest\\cabout\\new\\five.txt");
    DeleteFileA("msitest\\cabout\\four.txt");
    DeleteFileA("msitest\\second\\three.txt");
    DeleteFileA("msitest\\first\\two.txt");
    DeleteFileA("msitest\\one.txt");
    DeleteFileA("msitest\\filename");
    RemoveDirectoryA("msitest\\cabout\\new");
    RemoveDirectoryA("msitest\\cabout");
    RemoveDirectoryA("msitest\\second");
    RemoveDirectoryA("msitest\\first");
    RemoveDirectoryA("msitest");
}