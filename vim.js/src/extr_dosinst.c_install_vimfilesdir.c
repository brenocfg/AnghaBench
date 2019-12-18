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
 int BUFSIZE ; 
 int TABLE_SIZE (char**) ; 
 int /*<<< orphan*/  dir_remove_last (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  installdir ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  vim_mkdir (char*,int) ; 
 int vimfiles_dir_choice ; 
#define  vimfiles_dir_home 130 
#define  vimfiles_dir_none 129 
#define  vimfiles_dir_vim 128 
 char** vimfiles_subdirs ; 

__attribute__((used)) static void
install_vimfilesdir(int idx)
{
    int i;
    char *p;
    char vimdir_path[BUFSIZE];
    char vimfiles_path[BUFSIZE];
    char tmp_dirname[BUFSIZE];

    /* switch on the location that the user wants the plugin directories
     * built in */
    switch (vimfiles_dir_choice)
    {
	case vimfiles_dir_vim:
	{
	    /* Go to the %VIM% directory - check env first, then go one dir
	     *	   below installdir if there is no %VIM% environment variable.
	     *	   The accuracy of $VIM is checked in inspect_system(), so we
	     *	   can be sure it is ok to use here. */
	    p = getenv("VIM");
	    if (p == NULL) /* No $VIM in path */
		dir_remove_last(installdir, vimdir_path);
	    else
		strcpy(vimdir_path, p);
	    break;
	}
	case vimfiles_dir_home:
	{
	    /* Find the $HOME directory.  Its existence was already checked. */
	    p = getenv("HOME");
	    if (p == NULL)
	    {
		printf("Internal error: $HOME is NULL\n");
		p = "c:\\";
	    }
	    strcpy(vimdir_path, p);
	    break;
	}
	case vimfiles_dir_none:
	{
	    /* Do not create vim plugin directory */
	    return;
	}
    }

    /* Now, just create the directory.	If it already exists, it will fail
     * silently.  */
    sprintf(vimfiles_path, "%s\\vimfiles", vimdir_path);
    vim_mkdir(vimfiles_path, 0755);

    printf("Creating the following directories in \"%s\":\n", vimfiles_path);
    for (i = 0; i < TABLE_SIZE(vimfiles_subdirs); i++)
    {
	sprintf(tmp_dirname, "%s\\%s", vimfiles_path, vimfiles_subdirs[i]);
	printf("  %s", vimfiles_subdirs[i]);
	vim_mkdir(tmp_dirname, 0755);
    }
    printf("\n");
}