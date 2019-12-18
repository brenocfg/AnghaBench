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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* zlibVersion () ; 

void help(int exitval)
{
  printf("untgz version 0.2.1\n"
         "  using zlib version %s\n\n",
         zlibVersion());
  printf("Usage: untgz file.tgz            extract all files\n"
         "       untgz file.tgz fname ...  extract selected files\n"
         "       untgz -l file.tgz         list archive contents\n"
         "       untgz -h                  display this help\n");
  exit(exitval);
}