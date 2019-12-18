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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ _unlink (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ mkdir (char*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_unlink(void)
{
    FILE* file;
    ok(mkdir("test_unlink") == 0, "unable to create test dir\n");
    file = fopen("test_unlink\\empty", "w");
    ok(file != NULL, "unable to create test file\n");
    if(file)
      fclose(file);
    ok(_unlink("test_unlink") != 0, "unlinking a non-empty directory must fail\n");
    unlink("test_unlink\\empty");
    rmdir("test_unlink");
}