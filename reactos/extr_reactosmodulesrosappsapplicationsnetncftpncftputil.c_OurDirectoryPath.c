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
 char* Path (char* const,size_t const,int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  gOurDirectoryPath ; 

char *
OurDirectoryPath(char *const dst, const size_t siz, const char *const fname)
{
	return (Path(dst, siz, gOurDirectoryPath, fname));
}