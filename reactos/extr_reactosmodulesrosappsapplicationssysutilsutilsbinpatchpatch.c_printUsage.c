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
 char** m_argv ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
printUsage()
{
   printf("Usage:\n"
          "%s -c     - Create patch\n"
          "%s -d     - Dump patch\n"
          "%s        - Apply patch\n"
          "\n"
          "A patch can be created like this:\n"
          "%s -c \"patch name\" output.exe file1.orig file1.patched[ file2.orig file2.patched[ ...]]\n",
          m_argv[0], m_argv[0], m_argv[0], m_argv[0]);
}