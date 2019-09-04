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
 int FTPPutFiles3 (int /*<<< orphan*/  const,char const* const,char const* const,int const,int const,int const,int const,char const* const,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoConfirmResumeUploadProc ; 
 int /*<<< orphan*/  kDeleteNo ; 
 int /*<<< orphan*/  kResumeNo ; 

int
FTPPutFiles2(const FTPCIPtr cip, const char *const pattern, const char *const dstdir, const int recurse, const int doGlob, const int xtype, const int appendflag, const char *const tmppfx, const char *const tmpsfx)
{
	return (FTPPutFiles3(cip, pattern, dstdir, recurse, doGlob, xtype, appendflag, tmppfx, tmpsfx, kResumeNo, kDeleteNo, NoConfirmResumeUploadProc, 0));
}