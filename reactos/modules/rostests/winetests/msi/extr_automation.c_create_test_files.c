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
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_file (char*,int) ; 

__attribute__((used)) static void create_test_files(void)
{
    CreateDirectoryA("msitest", NULL);
    create_file("msitest\\one.txt", 100);
    CreateDirectoryA("msitest\\first", NULL);
    create_file("msitest\\first\\two.txt", 100);
    CreateDirectoryA("msitest\\second", NULL);
    create_file("msitest\\second\\three.txt", 100);
    CreateDirectoryA("msitest\\cabout",NULL);
    create_file("msitest\\cabout\\four.txt", 100);
    CreateDirectoryA("msitest\\cabout\\new",NULL);
    create_file("msitest\\cabout\\new\\five.txt", 100);
    create_file("msitest\\filename", 100);
}