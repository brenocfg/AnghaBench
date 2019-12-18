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
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_media_discoverer_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getchar () ; 
 int /*<<< orphan*/  libvlc_MediaListItemAdded ; 
 int /*<<< orphan*/  libvlc_MediaListItemDeleted ; 
 int libvlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_event_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int libvlc_media_discoverer_is_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_discoverer_media_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_discoverer_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  libvlc_media_discoverer_release (int /*<<< orphan*/ *) ; 
 int libvlc_media_discoverer_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_discoverer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_event_manager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_item_added ; 
 int /*<<< orphan*/  ml_item_deleted ; 
 int /*<<< orphan*/  test_log (char*,...) ; 

__attribute__((used)) static void
test_discoverer(libvlc_instance_t *p_vlc, const char *psz_name, bool b_wait)
{
    test_log("creating and starting discoverer %s\n", psz_name);

    libvlc_media_discoverer_t *p_md =
        libvlc_media_discoverer_new(p_vlc, psz_name);
    assert(p_md != NULL);

    libvlc_media_list_t *p_ml = libvlc_media_discoverer_media_list(p_md);
    assert(p_ml != NULL);

    libvlc_event_manager_t *p_evm = libvlc_media_list_event_manager(p_ml);
    assert(p_evm);

    int i_ret;
    i_ret = libvlc_event_attach(p_evm, libvlc_MediaListItemAdded,
                                ml_item_added, NULL);
    assert(i_ret == 0);
    i_ret = libvlc_event_attach(p_evm, libvlc_MediaListItemDeleted,
                                ml_item_deleted, NULL);
    assert(i_ret == 0);

    if (libvlc_media_discoverer_start(p_md) == -1)
    {
        test_log("warn: could not start md (not critical)\n");
    }
    else
    {
        assert(libvlc_media_discoverer_is_running(p_md));
        if (b_wait)
        {
            test_log("Press any keys to stop\n");
            getchar();
        }
        libvlc_media_discoverer_stop(p_md);
    }

    libvlc_event_detach(p_evm, libvlc_MediaListItemAdded,
                        ml_item_added, NULL);
    libvlc_event_detach(p_evm, libvlc_MediaListItemDeleted,
                        ml_item_deleted, NULL);

    libvlc_media_list_release(p_ml);
    libvlc_media_discoverer_release(p_md);
}