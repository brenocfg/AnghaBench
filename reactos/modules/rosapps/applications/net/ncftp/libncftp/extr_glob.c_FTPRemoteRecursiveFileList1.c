#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cwd ;
struct TYPE_6__ {int /*<<< orphan*/  serverType; } ;
typedef  int /*<<< orphan*/  LineList ;
typedef  int /*<<< orphan*/  FileInfoListPtr ;
typedef  int /*<<< orphan*/  FileInfoList ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeRNames (int /*<<< orphan*/ *,char* const,int,int) ; 
 int /*<<< orphan*/  ConcatFileInfoList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConcatFileToFileInfoList (int /*<<< orphan*/ ,char* const) ; 
 int /*<<< orphan*/  DisposeFileInfoListContents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DisposeLineListContents (int /*<<< orphan*/ *) ; 
 int FTPChdir (TYPE_1__*,char* const) ; 
 int FTPGetCWD (TYPE_1__*,char*,int) ; 
 int FTPListToMemory2 (TYPE_1__*,char*,int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  InitFileInfoList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnLslR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kNoErr ; 

int
FTPRemoteRecursiveFileList1(FTPCIPtr cip, char *const rdir, FileInfoListPtr files)
{
	LineList dirContents;
	FileInfoList fil;
	char cwd[512];
	int result;

	if ((result = FTPGetCWD(cip, cwd, sizeof(cwd))) < 0)
		return (result);

	InitFileInfoList(files);

	if (rdir == NULL)
		return (-1);

	if (FTPChdir(cip, rdir) < 0) {
		/* Probably not a directory.
		 * Just add it as a plain file
		 * to the list.
		 */
		(void) ConcatFileToFileInfoList(files, rdir);
		return (kNoErr);
	}

	/* Paths collected must be relative. */
	if ((result = FTPListToMemory2(cip, "", &dirContents, "-lRa", 1, (int *) 0)) < 0) {
		if ((result = FTPChdir(cip, cwd)) < 0) {
			return (result);
		}
	}

	(void) UnLslR(&fil, &dirContents, cip->serverType);
	DisposeLineListContents(&dirContents);
	/* Could sort it to breadth-first here. */
	/* (void) SortRecursiveFileList(&fil); */
	(void) ComputeRNames(&fil, rdir, 1, 1);
	(void) ConcatFileInfoList(files, &fil);
	DisposeFileInfoListContents(&fil);

	if ((result = FTPChdir(cip, cwd)) < 0) {
		return (result);
	}
	return (kNoErr);
}