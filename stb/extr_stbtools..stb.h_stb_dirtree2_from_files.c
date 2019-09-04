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
typedef  int /*<<< orphan*/  stb_dirtree2 ;

/* Variables and functions */
 int /*<<< orphan*/ * stb_dirtree2_from_files_relative (char*,char**,int) ; 

stb_dirtree2 *stb_dirtree2_from_files(char **filelist, int count)
{
   return stb_dirtree2_from_files_relative((char*) "", filelist, count);
}