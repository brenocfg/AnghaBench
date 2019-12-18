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
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
#define  no_argument 128 
 scalar_t__ setenv (char*,char const*,int) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  version () ; 

int main (int argc, char *argv[])
{
#ifdef HAVE_GETOPT_H
    static const struct option opts[] =
    {
        { "help",       no_argument,       NULL, 'h' },
        { "version",    no_argument,       NULL, 'V' },
        { NULL,         no_argument,       NULL, '\0'}
    };

    int c;

    while ((c = getopt_long (argc, argv, "hV", opts, NULL)) != -1)
        switch (c)
        {
            case 'h':
                usage (argv[0]);
                return 0;
            case 'V':
                version ();
                return 0;
            default:
                usage (argv[0]);
                return 1;
        }
#else
    int optind = 1;
#endif

    for (int i = optind; i < argc; i++)
    {
        const char *path = argv[i];

        if (setenv ("VLC_PLUGIN_PATH", path, 1))
            abort ();

        const char *vlc_argv[4];
        int vlc_argc = 0;

        vlc_argv[vlc_argc++] = "--quiet";
        vlc_argv[vlc_argc++] = "--reset-plugins-cache";
        vlc_argv[vlc_argc++] = "--"; /* end of options */
        vlc_argv[vlc_argc] = NULL;

        libvlc_instance_t *vlc = libvlc_new (vlc_argc, vlc_argv);
        if (vlc == NULL)
            return 1;
        libvlc_release(vlc);
    }

    return 0;
}