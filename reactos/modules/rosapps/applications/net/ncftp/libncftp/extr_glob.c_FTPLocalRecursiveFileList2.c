#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct Stat {scalar_t__ st_size; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ longest_int ;
struct TYPE_8__ {char type; int /*<<< orphan*/ * plug; int /*<<< orphan*/ * rlinkto; scalar_t__ size; int /*<<< orphan*/  mdtm; void* lname; int /*<<< orphan*/ * rname; void* relname; } ;
struct TYPE_7__ {TYPE_1__* first; } ;
struct TYPE_6__ {char* line; struct TYPE_6__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__* LineListPtr ;
typedef  int /*<<< orphan*/  FileInfoListPtr ;
typedef  TYPE_3__ FileInfo ;
typedef  int /*<<< orphan*/  FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  AddFileInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  Error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  InitFileInfoList (int /*<<< orphan*/ ) ; 
 scalar_t__ Lstat (char*,struct Stat*) ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 void* StrDup (char*) ; 
 char* StrRFindLocalPathDelim (char*) ; 
 int /*<<< orphan*/  Traverse (int /*<<< orphan*/ ,char*,struct Stat*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MAX_PATH ; 
 int /*<<< orphan*/  kDoPerror ; 
 int kNoErr ; 
 scalar_t__ strcmp (char*,char*) ; 

int
FTPLocalRecursiveFileList2(FTPCIPtr cip, LineListPtr fileList, FileInfoListPtr files, int erelative)
{
	LinePtr filePtr, nextFilePtr;
#if defined(WIN32) || defined(_WINDOWS)
	char fullpath[_MAX_PATH + 1];
	char relpath[_MAX_PATH + 1];
#else
	char fullpath[512];
	char relpath[512];
#endif
	struct Stat st;
	FileInfo fi;
	char *cp;

	InitFileInfoList(files);

	for (filePtr = fileList->first;
		filePtr != NULL;
		filePtr = nextFilePtr)
	{
		nextFilePtr = filePtr->next;

		(void) STRNCPY(fullpath, filePtr->line);	/* initialize fullpath */
		if ((erelative != 0) || (strcmp(filePtr->line, ".") == 0) || (filePtr->line[0] == '\0'))
			(void) STRNCPY(relpath, "");
		else if ((cp = StrRFindLocalPathDelim(filePtr->line)) == NULL)
			(void) STRNCPY(relpath, filePtr->line);
		else
			(void) STRNCPY(relpath, cp + 1);
		if (Lstat(fullpath, &st) < 0) {
			Error(cip, kDoPerror, "could not stat %s.\n", fullpath);
			continue;
		}

		if (S_ISDIR(st.st_mode) == 0) {
			fi.relname = StrDup(relpath);
			fi.rname = NULL;
			fi.lname = StrDup(fullpath);
			fi.mdtm = st.st_mtime;
			fi.size = (longest_int) st.st_size;
			fi.rlinkto = NULL;
			fi.plug = NULL;
			fi.type = '-';
			(void) AddFileInfo(files, &fi);
			continue;			/* wasn't a directory */
		}

		/* Paths collected must be relative. */
		Traverse(cip, fullpath, &st, relpath, files);
	}
	return (kNoErr);
}