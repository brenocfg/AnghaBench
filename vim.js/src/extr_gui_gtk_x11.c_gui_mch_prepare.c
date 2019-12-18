#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int flags; } ;
typedef  TYPE_1__ cmdline_option_T ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {void* starting; void* dofork; scalar_t__ geom; } ;

/* Variables and functions */
#define  ARG_BACKGROUND 136 
 int ARG_COMPAT_LONG ; 
#define  ARG_FONT 135 
#define  ARG_FOREGROUND 134 
 int ARG_FOR_GTK ; 
#define  ARG_GEOMETRY 133 
 int ARG_HAS_VALUE ; 
#define  ARG_ICONIC 132 
 int ARG_INDEX_MASK ; 
 int ARG_KEEP ; 
 int ARG_NEEDS_GUI ; 
#define  ARG_NETBEANS 131 
#define  ARG_NOREVERSE 130 
#define  ARG_REVERSE 129 
#define  ARG_ROLE 128 
 void* FALSE ; 
 int /*<<< orphan*/  G_DIR_SEPARATOR ; 
 int MAXPATHL ; 
 scalar_t__ OK ; 
 void* TRUE ; 
 char* abs_restart_command ; 
 scalar_t__ alloc (unsigned int) ; 
 char* background_argument ; 
 TYPE_1__* cmdline_options ; 
 char* font_argument ; 
 char* foreground_argument ; 
 void* found_iconic_arg ; 
 void* found_reverse_arg ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 
 size_t gui_argc ; 
 char** gui_argv ; 
 scalar_t__ mch_FullName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  mch_memmove (char**,char**,int) ; 
 char* netbeansArg ; 
 char* restart_command ; 
 char* role_argument ; 
 int /*<<< orphan*/ * strchr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ *,char) ; 
 scalar_t__ vim_strsave (int /*<<< orphan*/ *) ; 

void
gui_mch_prepare(int *argc, char **argv)
{
    const cmdline_option_T  *option;
    int			    i	= 0;
    int			    len = 0;

#if defined(FEAT_GUI_GNOME) && defined(FEAT_SESSION)
    /*
     * Determine the command used to invoke Vim, to be passed as restart
     * command to the session manager.	If argv[0] contains any directory
     * components try building an absolute path, otherwise leave it as is.
     */
    restart_command = argv[0];

    if (strchr(argv[0], G_DIR_SEPARATOR) != NULL)
    {
	char_u buf[MAXPATHL];

	if (mch_FullName((char_u *)argv[0], buf, (int)sizeof(buf), TRUE) == OK)
	{
	    abs_restart_command = (char *)vim_strsave(buf);
	    restart_command = abs_restart_command;
	}
    }
#endif

    /*
     * Move all the entries in argv which are relevant to GTK+ and GNOME
     * into gui_argv.  Freed later in gui_mch_init().
     */
    gui_argc = 0;
    gui_argv = (char **)alloc((unsigned)((*argc + 1) * sizeof(char *)));

    g_return_if_fail(gui_argv != NULL);

    gui_argv[gui_argc++] = argv[i++];

    while (i < *argc)
    {
	/* Don't waste CPU cycles on non-option arguments. */
	if (argv[i][0] != '-' && argv[i][0] != '+')
	{
	    ++i;
	    continue;
	}

	/* Look for argv[i] in cmdline_options[] table. */
	for (option = &cmdline_options[0]; option->name != NULL; ++option)
	{
	    len = strlen(option->name);

	    if (strncmp(argv[i], option->name, len) == 0)
	    {
		if (argv[i][len] == '\0')
		    break;
		/* allow --foo=bar style */
		if (argv[i][len] == '=' && (option->flags & ARG_HAS_VALUE))
		    break;
#ifdef FEAT_NETBEANS_INTG
		/* darn, -nb has non-standard syntax */
		if (vim_strchr((char_u *)":=", argv[i][len]) != NULL
			&& (option->flags & ARG_INDEX_MASK) == ARG_NETBEANS)
		    break;
#endif
	    }
	    else if ((option->flags & ARG_COMPAT_LONG)
			&& strcmp(argv[i], option->name + 1) == 0)
	    {
		/* Replace the standard X arguments "-name" and "-display"
		 * with their GNU-style long option counterparts. */
		argv[i] = (char *)option->name;
		break;
	    }
	}
	if (option->name == NULL) /* no match */
	{
	    ++i;
	    continue;
	}

	if (option->flags & ARG_FOR_GTK)
	{
	    /* Move the argument into gui_argv, which
	     * will later be passed to gtk_init_check() */
	    gui_argv[gui_argc++] = argv[i];
	}
	else
	{
	    char *value = NULL;

	    /* Extract the option's value if there is one.
	     * Accept both "--foo bar" and "--foo=bar" style. */
	    if (option->flags & ARG_HAS_VALUE)
	    {
		if (argv[i][len] == '=')
		    value = &argv[i][len + 1];
		else if (i + 1 < *argc && strcmp(argv[i + 1], "--") != 0)
		    value = argv[i + 1];
	    }

	    /* Check for options handled by Vim itself */
	    switch (option->flags & ARG_INDEX_MASK)
	    {
		case ARG_REVERSE:
		    found_reverse_arg = TRUE;
		    break;
		case ARG_NOREVERSE:
		    found_reverse_arg = FALSE;
		    break;
		case ARG_FONT:
		    font_argument = value;
		    break;
		case ARG_GEOMETRY:
		    if (value != NULL)
			gui.geom = vim_strsave((char_u *)value);
		    break;
		case ARG_BACKGROUND:
		    background_argument = value;
		    break;
		case ARG_FOREGROUND:
		    foreground_argument = value;
		    break;
		case ARG_ICONIC:
		    found_iconic_arg = TRUE;
		    break;
		case ARG_ROLE:
		    role_argument = value; /* used later in gui_mch_open() */
		    break;
#ifdef FEAT_NETBEANS_INTG
		case ARG_NETBEANS:
		    gui.dofork = FALSE; /* don't fork() when starting GUI */
		    netbeansArg = argv[i];
		    break;
#endif
		default:
		    break;
	    }
	}

	/* These arguments make gnome_program_init() print a message and exit.
	 * Must start the GUI for this, otherwise ":gui" will exit later! */
	if (option->flags & ARG_NEEDS_GUI)
	    gui.starting = TRUE;

	if (option->flags & ARG_KEEP)
	    ++i;
	else
	{
	    /* Remove the flag from the argument vector. */
	    if (--*argc > i)
	    {
		int n_strip = 1;

		/* Move the argument's value as well, if there is one. */
		if ((option->flags & ARG_HAS_VALUE)
			&& argv[i][len] != '='
			&& strcmp(argv[i + 1], "--") != 0)
		{
		    ++n_strip;
		    --*argc;
		    if (option->flags & ARG_FOR_GTK)
			gui_argv[gui_argc++] = argv[i + 1];
		}

		if (*argc > i)
		    mch_memmove(&argv[i], &argv[i + n_strip],
						(*argc - i) * sizeof(char *));
	    }
	    argv[*argc] = NULL;
	}
    }

    gui_argv[gui_argc] = NULL;
}