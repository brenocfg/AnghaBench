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
typedef  int /*<<< orphan*/  LineListPtr ;
typedef  int /*<<< orphan*/  FTPCIPtr ;

/* Variables and functions */
 int FTPListToMemory2 (int /*<<< orphan*/  const,char const* const,int /*<<< orphan*/  const,char const* const,int,int*) ; 

int
FTPListToMemory(const FTPCIPtr cip, const char *const pattern, const LineListPtr llines, const char *const lsflags)
{
	return (FTPListToMemory2(cip, pattern, llines, lsflags, 1, (int *) 0));
}