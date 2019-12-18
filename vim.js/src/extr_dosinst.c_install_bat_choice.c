#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t arg; } ;
struct TYPE_3__ {char* batpath; char* oldbat; char* exenamearg; char* exearg; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char NUL ; 
 char* VIM_VERSION_NODOT ; 
 TYPE_2__* choices ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* installdir ; 
 int need_uninstall_entry ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 TYPE_1__* targets ; 

__attribute__((used)) static void
install_bat_choice(int idx)
{
    char	*batpath = targets[choices[idx].arg].batpath;
    char	*oldname = targets[choices[idx].arg].oldbat;
    char	*exename = targets[choices[idx].arg].exenamearg;
    char	*vimarg = targets[choices[idx].arg].exearg;
    FILE	*fd;

    if (*batpath != NUL)
    {
	fd = fopen(batpath, "w");
	if (fd == NULL)
	    printf("\nERROR: Cannot open \"%s\" for writing.\n", batpath);
	else
	{
	    need_uninstall_entry = 1;

	    fprintf(fd, "@echo off\n");
	    fprintf(fd, "rem -- Run Vim --\n");
	    fprintf(fd, "\n");

	    /* Don't use double quotes for the "set" argument, also when it
	     * contains a space.  The quotes would be included in the value
	     * for MSDOS and NT.
	     * The order of preference is:
	     * 1. $VIMRUNTIME/vim.exe	    (user preference)
	     * 2. $VIM/vim70/vim.exe	    (hard coded version)
	     * 3. installdir/vim.exe	    (hard coded install directory)
	     */
	    fprintf(fd, "set VIM_EXE_DIR=%s\n", installdir);
	    fprintf(fd, "if exist \"%%VIM%%\\%s\\%s\" set VIM_EXE_DIR=%%VIM%%\\%s\n",
			       VIM_VERSION_NODOT, exename, VIM_VERSION_NODOT);
	    fprintf(fd, "if exist \"%%VIMRUNTIME%%\\%s\" set VIM_EXE_DIR=%%VIMRUNTIME%%\n", exename);
	    fprintf(fd, "\n");

	    /* Give an error message when the executable could not be found. */
	    fprintf(fd, "if exist \"%%VIM_EXE_DIR%%\\%s\" goto havevim\n",
								     exename);
	    fprintf(fd, "echo \"%%VIM_EXE_DIR%%\\%s\" not found\n", exename);
	    fprintf(fd, "goto eof\n");
	    fprintf(fd, "\n");
	    fprintf(fd, ":havevim\n");

	    fprintf(fd, "rem collect the arguments in VIMARGS for Win95\n");
	    fprintf(fd, "set VIMARGS=\n");
	    if (*exename == 'g')
		fprintf(fd, "set VIMNOFORK=\n");
	    fprintf(fd, ":loopstart\n");
	    fprintf(fd, "if .%%1==. goto loopend\n");
	    if (*exename == 'g')
	    {
		fprintf(fd, "if NOT .%%1==.-f goto noforkarg\n");
		fprintf(fd, "set VIMNOFORK=1\n");
		fprintf(fd, ":noforkarg\n");
	    }
	    fprintf(fd, "set VIMARGS=%%VIMARGS%% %%1\n");
	    fprintf(fd, "shift\n");
	    fprintf(fd, "goto loopstart\n");
	    fprintf(fd, ":loopend\n");
	    fprintf(fd, "\n");

	    fprintf(fd, "if .%%OS%%==.Windows_NT goto ntaction\n");
	    fprintf(fd, "\n");

	    /* For gvim.exe use "start" to avoid that the console window stays
	     * open. */
	    if (*exename == 'g')
	    {
		fprintf(fd, "if .%%VIMNOFORK%%==.1 goto nofork\n");
		fprintf(fd, "start ");
	    }

	    /* Always use quotes, $VIM or $VIMRUNTIME might have a space. */
	    fprintf(fd, "\"%%VIM_EXE_DIR%%\\%s\" %s %%VIMARGS%%\n",
							     exename, vimarg);
	    fprintf(fd, "goto eof\n");
	    fprintf(fd, "\n");

	    if (*exename == 'g')
	    {
		fprintf(fd, ":nofork\n");
		fprintf(fd, "start /w ");
		/* Always use quotes, $VIM or $VIMRUNTIME might have a space. */
		fprintf(fd, "\"%%VIM_EXE_DIR%%\\%s\" %s %%VIMARGS%%\n",
							     exename, vimarg);
		fprintf(fd, "goto eof\n");
		fprintf(fd, "\n");
	    }

	    fprintf(fd, ":ntaction\n");
	    fprintf(fd, "rem for WinNT we can use %%*\n");

	    /* For gvim.exe use "start /b" to avoid that the console window
	     * stays open. */
	    if (*exename == 'g')
	    {
		fprintf(fd, "if .%%VIMNOFORK%%==.1 goto noforknt\n");
		fprintf(fd, "start \"dummy\" /b ");
	    }

	    /* Always use quotes, $VIM or $VIMRUNTIME might have a space. */
	    fprintf(fd, "\"%%VIM_EXE_DIR%%\\%s\" %s %%*\n", exename, vimarg);
	    fprintf(fd, "goto eof\n");
	    fprintf(fd, "\n");

	    if (*exename == 'g')
	    {
		fprintf(fd, ":noforknt\n");
		fprintf(fd, "start \"dummy\" /b /wait ");
		/* Always use quotes, $VIM or $VIMRUNTIME might have a space. */
		fprintf(fd, "\"%%VIM_EXE_DIR%%\\%s\" %s %%*\n",
							     exename, vimarg);
	    }

	    fprintf(fd, "\n:eof\n");
	    fprintf(fd, "set VIMARGS=\n");
	    if (*exename == 'g')
		fprintf(fd, "set VIMNOFORK=\n");

	    fclose(fd);
	    printf("%s has been %s\n", batpath,
				 oldname == NULL ? "created" : "overwritten");
	}
    }
}