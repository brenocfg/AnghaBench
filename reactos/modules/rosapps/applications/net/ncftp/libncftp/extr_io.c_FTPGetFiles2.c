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
typedef  int /*<<< orphan*/  ConfirmResumeDownloadProc ;

/* Variables and functions */
 int FTPGetFiles3 (int /*<<< orphan*/  const,char const* const,char const* const,int const,int const,int const,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kDeleteNo ; 
 int /*<<< orphan*/  kTarYes ; 

int
FTPGetFiles2(const FTPCIPtr cip, const char *const pattern, const char *const dstdir, const int recurse, const int doGlob, const int xtype, const int resumeflag, const int appendflag)
{
	return (FTPGetFiles3(cip, pattern, dstdir, recurse, doGlob, xtype, resumeflag, appendflag, kDeleteNo, kTarYes, (ConfirmResumeDownloadProc) 0, 0));
}