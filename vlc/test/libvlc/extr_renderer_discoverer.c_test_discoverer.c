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
typedef  int /*<<< orphan*/  libvlc_renderer_discoverer_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getchar () ; 
 int /*<<< orphan*/  libvlc_RendererDiscovererItemAdded ; 
 int /*<<< orphan*/  libvlc_RendererDiscovererItemDeleted ; 
 int libvlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_renderer_discoverer_event_manager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_renderer_discoverer_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  libvlc_renderer_discoverer_release (int /*<<< orphan*/ *) ; 
 int libvlc_renderer_discoverer_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_renderer_discoverer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renderer_discoverer_item_added ; 
 int /*<<< orphan*/  renderer_discoverer_item_deleted ; 
 int /*<<< orphan*/  test_log (char*,...) ; 

__attribute__((used)) static void
test_discoverer(libvlc_instance_t *p_vlc, const char *psz_name)
{
    test_log("creating and starting discoverer %s\n", psz_name);

    libvlc_renderer_discoverer_t *p_rd =
        libvlc_renderer_discoverer_new(p_vlc, psz_name);
    assert(p_rd != NULL);

    libvlc_event_manager_t *p_evm = libvlc_renderer_discoverer_event_manager(p_rd);
    assert(p_evm);

    int i_ret;
    i_ret = libvlc_event_attach(p_evm, libvlc_RendererDiscovererItemAdded,
                                renderer_discoverer_item_added, NULL);
    assert(i_ret == 0);
    i_ret = libvlc_event_attach(p_evm, libvlc_RendererDiscovererItemDeleted,
                                renderer_discoverer_item_deleted, NULL);
    assert(i_ret == 0);

    if (libvlc_renderer_discoverer_start(p_rd) == -1)
    {
        test_log("warn: could not start md (not critical)\n");
    }
    else
    {
        test_log("Press any keys to stop\n");
        getchar();
        libvlc_renderer_discoverer_stop(p_rd);
    }

    libvlc_renderer_discoverer_release(p_rd);
}