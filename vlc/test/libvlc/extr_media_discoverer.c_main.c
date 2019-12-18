#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {scalar_t__ i_cat; char* psz_name; int /*<<< orphan*/  psz_longname; } ;
typedef  TYPE_1__ libvlc_media_discoverer_description_t ;
typedef  scalar_t__ libvlc_media_discoverer_category_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ libvlc_media_discoverer_devices ; 
 scalar_t__ libvlc_media_discoverer_lan ; 
 scalar_t__ libvlc_media_discoverer_list_get (int /*<<< orphan*/ *,scalar_t__,TYPE_1__***) ; 
 int /*<<< orphan*/  libvlc_media_discoverer_list_release (TYPE_1__**,scalar_t__) ; 
 scalar_t__ libvlc_media_discoverer_localdirs ; 
 int /*<<< orphan*/ * libvlc_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  test_defaults_args ; 
 int /*<<< orphan*/  test_defaults_nargs ; 
 int /*<<< orphan*/  test_discoverer (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  test_init () ; 
 int /*<<< orphan*/  test_log (char*,...) ; 

int
main(int i_argc, char *ppsz_argv[])
{
    test_init();

    char *psz_test_name = i_argc > 1 ? ppsz_argv[1] : NULL;

    libvlc_instance_t *p_vlc = libvlc_new(test_defaults_nargs,
                                          test_defaults_args);
    assert(p_vlc != NULL);

    if (psz_test_name != NULL)
    {
        /* Test a specific service discovery from command line */
        alarm(0);
        test_discoverer(p_vlc, psz_test_name, true);
        libvlc_release(p_vlc);
        return 0;
    }

    for(libvlc_media_discoverer_category_t i_cat = libvlc_media_discoverer_devices;
        i_cat <= libvlc_media_discoverer_localdirs; i_cat ++)
    {
        test_log("== getting list of media_discoverer for %d category ==\n", i_cat);

        libvlc_media_discoverer_description_t **pp_services;
        ssize_t i_count =
            libvlc_media_discoverer_list_get(p_vlc, i_cat, &pp_services);
        if (i_count <= 0)
        {
            test_log("warn: no discoverers (not critical)\n");
            continue;
        }
        assert(pp_services != NULL);

        for (unsigned int i = 0; i < i_count; ++i)
        {
            libvlc_media_discoverer_description_t *p_service = pp_services[i];

            assert(i_cat == p_service->i_cat);
            test_log("= discoverer: name: '%s', longname: '%s' =\n",
                     p_service->psz_name, p_service->psz_longname);

#if 0
            if (!strncasecmp(p_service->psz_name, "podcast", 7)
             || i_cat == libvlc_media_discoverer_lan)
            {
                /* see comment in libvlc_media_discoverer_new() */
                continue;
            }
            test_discoverer(p_vlc, p_service->psz_name, false);
#endif
        }
        libvlc_media_discoverer_list_release(pp_services, i_count);
    }
    libvlc_release(p_vlc);

    return 0;
}