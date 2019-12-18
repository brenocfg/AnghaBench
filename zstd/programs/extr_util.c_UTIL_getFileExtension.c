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
 char* strrchr (char const*,char) ; 

const char* UTIL_getFileExtension(const char* infilename)
{
   const char* extension = strrchr(infilename, '.');
   if(!extension || extension==infilename) return "";
   return extension;
}