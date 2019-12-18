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
struct option {char* member_0; char member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  chmhttp_server (char*) ; 
 char* config_bind ; 
 int /*<<< orphan*/  config_port ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  no_argument ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  required_argument ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int c, char **v)
{
#ifdef CHM_HTTP_SIMPLE
    if (c < 2)
        usage(v[0]);

    /* run the server */
    chmhttp_server(v[1]);

#else
    int optindex = 0;

    struct option longopts[] = 
    {
        { "port", required_argument, 0, 'p' },
        { "bind", required_argument, 0, 'b' },
        { "help", no_argument, 0, 'h' },
        { 0, 0, 0, 0 }
    };

    while (1) 
    {
        int o;
        o = getopt_long (c, v, "n:b:h", longopts, &optindex);
        if (o < 0) 
        {
            break;
        }

        switch (o) 
        {
            case 'p':
                config_port = atoi (optarg);
                if (config_port <= 0) 
                {
                    fprintf(stderr, "bad port number (%s)\n", optarg);
                    exit(1);
                }
                break;

            case 'b':
                strncpy (config_bind, optarg, 65536);
                config_bind[65535] = '\0';
                break;

            case 'h':
                usage (v[0]);
                break;
        }

    }

    if (optind + 1 != c)
    {
        usage (v[0]);
    }

    /* run the server */
    chmhttp_server(v[optind]);
#endif

    /* NOT REACHED */
    return 0;
}