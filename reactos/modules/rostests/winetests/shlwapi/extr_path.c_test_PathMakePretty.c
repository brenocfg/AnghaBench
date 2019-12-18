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
 scalar_t__ FALSE ; 
 int MAX_PATH ; 
 scalar_t__ PathMakePrettyA (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_PathMakePretty(void)
{
   char buff[MAX_PATH];

   ok (PathMakePrettyA(NULL) == FALSE, "PathMakePretty: NULL path succeeded\n");
   buff[0] = '\0';
   ok (PathMakePrettyA(buff) == TRUE, "PathMakePretty: Empty path failed\n");

   strcpy(buff, "C:\\A LONG FILE NAME WITH \\SPACES.TXT");
   ok (PathMakePrettyA(buff) == TRUE, "PathMakePretty: Long UC name failed\n");
   ok (strcmp(buff, "C:\\a long file name with \\spaces.txt") == 0,
       "PathMakePretty: Long UC name not changed\n");

   strcpy(buff, "C:\\A LONG FILE NAME WITH \\MixedCase.TXT");
   ok (PathMakePrettyA(buff) == FALSE, "PathMakePretty: Long MC name succeeded\n");
   ok (strcmp(buff, "C:\\A LONG FILE NAME WITH \\MixedCase.TXT") == 0,
       "PathMakePretty: Failed but modified path\n");

   strcpy(buff, "TEST");
   ok (PathMakePrettyA(buff) == TRUE,  "PathMakePretty: Short name failed\n");
   ok (strcmp(buff, "Test") == 0,  "PathMakePretty: 1st char lowercased %s\n", buff);
}