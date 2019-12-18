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
#define  ACTION_BREAK 137 
#define  ACTION_INSTALL 136 
#define  ACTION_LOAD 135 
#define  ACTION_NONE 134 
#define  ACTION_RELOAD 133 
#define  ACTION_STATUS 132 
#define  ACTION_TERMINAL 131 
#define  ACTION_TRANS 130 
#define  ACTION_UNINSTALL 129 
#define  ACTION_UNLOAD 128 
 int /*<<< orphan*/  change_symbols (int,char*) ; 
 int /*<<< orphan*/  close_debugger () ; 
 int /*<<< orphan*/  dobreak () ; 
 int /*<<< orphan*/  doterminal () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  process_file (char*) ; 
 int /*<<< orphan*/  showstatus () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tryinstall () ; 
 int /*<<< orphan*/  tryuninstall () ; 
 scalar_t__ ulGlobalVerbose ; 

int process_switches(int argc,char* argv[])
{
	int i;
	char* parg,*pfilename = NULL;
	int action = ACTION_NONE;
	int error = 0;

    // parse commandline arguments
	for(i=1;i<argc;i++)
	{
		parg = argv[i];
		if(*parg == '-')
		{
		    int new_action=ACTION_NONE;

			parg++;
			if(strcmp(parg,"load")==0 || strcmp(parg,"l")==0)
			{
				new_action = ACTION_LOAD;
			}
			else if(strcmp(parg,"unload")==0 || strcmp(parg,"u")==0)
			{
				new_action = ACTION_UNLOAD;
			}
			else if(strcmp(parg,"trans")==0 || strcmp(parg,"t")==0)
            {
                new_action = ACTION_TRANS;
            }
			else if(strcmp(parg,"reload")==0 || strcmp(parg,"r")==0)
            {
                new_action = ACTION_RELOAD;
            }
			else if(strcmp(parg,"verbose")==0 || strcmp(parg,"v")==0)
            {
			    if( ulGlobalVerbose+1 > ulGlobalVerbose )
				    ulGlobalVerbose++;
            }
			else if(strcmp(parg,"install")==0 || strcmp(parg,"i")==0)
            {
                new_action = ACTION_INSTALL;
            }
			else if(strcmp(parg,"uninstall")==0 || strcmp(parg,"x")==0)
            {
                new_action = ACTION_UNINSTALL;
            }
			else if(strcmp(parg,"status")==0 || strcmp(parg,"s")==0)
            {
                new_action = ACTION_STATUS;
            }
			else if(strcmp(parg,"break")==0 || strcmp(parg,"b")==0)
            {
                new_action = ACTION_BREAK;
            }
			else if(strcmp(parg,"serial")==0 || strcmp(parg,"ser")==0)
            {
                new_action = ACTION_TERMINAL;
            }
			else
			{
				printf("LOADER: error: unknown switch %s", argv[i]);
				error = 1;
			}

            if( new_action != ACTION_NONE )
            {
                if( action == ACTION_NONE )
                    action = new_action;
                else
                if( action == new_action )
                {
                    // identical, just ignore
                }
                else
                {
                    printf("LOADER: error: conflicting switch %s", argv[i]);
                    error = 1;
                }
            }
		}
		else
		{
            if( pfilename )
            {
                printf("LOADER: error: additional filename %s", parg);
                error = 1;
            }
			pfilename = parg;
		}
	}

    // check number of required parameters
    switch( action )
    {
        case ACTION_TRANS :
        case ACTION_LOAD :
        case ACTION_UNLOAD :
            if( !pfilename )
            {
                printf("LOADER: error: missing filename\n");
                error = 1;
            }
            break;
        case ACTION_RELOAD :
            /* filename parameter is optional */
            break;
#if 0
        case ACTION_UNINSTALL:
            close_debugger();
            tryuninstall();
            break;
        case ACTION_INSTALL:
            tryinstall();
            break;
#endif
        case ACTION_STATUS:
            showstatus();
            break;
        case ACTION_BREAK:
            dobreak();
            break;
#if 0
        case ACTION_TERMINAL:
            doterminal();
            break;
#endif
        case ACTION_NONE :
            printf("LOADER: no action specified specifed on commandline\n");
            error = 1;

            break;
        default :
            printf("LOADER: an internal error has occurred at commandline parsing\n");
            error = 1;
    }

    if( !error )    // commandline was fine, now start processing
    {
        switch( action )
        {
            case ACTION_TRANS :
                printf("LOADER: trying to translate file %s...\n",pfilename);
                if( process_file(pfilename)==0 )
                    printf("LOADER: file %s has been translated\n",pfilename);
                else
                    printf("LOADER: error while translating file %s\n",pfilename);
                break;
            case ACTION_LOAD :
            case ACTION_UNLOAD :
            case ACTION_RELOAD :
                change_symbols(action,pfilename);
                break;
        }
    }

    return error;
}