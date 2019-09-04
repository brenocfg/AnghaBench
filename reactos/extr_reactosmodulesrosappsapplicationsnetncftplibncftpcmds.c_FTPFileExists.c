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
typedef  int /*<<< orphan*/  FTPCIPtr ;

/* Variables and functions */
 int FTPFileExists2 (int /*<<< orphan*/  const,char const* const,int,int,int,int,int) ; 

int
FTPFileExists(const FTPCIPtr cip, const char *const file)
{
	return (FTPFileExists2(cip, file, 1, 1, 1, 1, 1));
}