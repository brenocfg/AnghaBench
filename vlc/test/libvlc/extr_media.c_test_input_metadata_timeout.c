#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_sem_t ;
struct input_preparser_callbacks_t {int /*<<< orphan*/  on_preparse_ended; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_LOCAL ; 
 int META_REQUEST_OPTION_FETCH_LOCAL ; 
 int META_REQUEST_OPTION_SCOPE_LOCAL ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * input_item_NewFile (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_preparse_timeout ; 
 int /*<<< orphan*/  libvlc_MetadataCancel (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int libvlc_MetadataRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct input_preparser_callbacks_t const*,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  test_log (char*,int,int) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_pipe (int*) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_input_metadata_timeout(libvlc_instance_t *vlc, int timeout,
                                        int wait_and_cancel)
{
    test_log ("test_input_metadata_timeout: timeout: %d, wait_and_cancel: %d ms\n",
         timeout, wait_and_cancel);

    int i_ret, p_pipe[2];
    i_ret = vlc_pipe(p_pipe);
    assert(i_ret == 0 && p_pipe[1] >= 0);

    char psz_fd_uri[strlen("fd://") + 11];
    sprintf(psz_fd_uri, "fd://%u", (unsigned) p_pipe[1]);
    input_item_t *p_item = input_item_NewFile(psz_fd_uri, "test timeout", 0,
                                              ITEM_LOCAL);
    assert(p_item != NULL);

    vlc_sem_t sem;
    vlc_sem_init (&sem, 0);
    const struct input_preparser_callbacks_t cbs = {
        .on_preparse_ended = input_item_preparse_timeout,
    };
    i_ret = libvlc_MetadataRequest(vlc->p_libvlc_int, p_item,
                                   META_REQUEST_OPTION_SCOPE_LOCAL |
                                   META_REQUEST_OPTION_FETCH_LOCAL,
                                   &cbs, &sem, timeout, vlc);
    assert(i_ret == 0);

    if (wait_and_cancel > 0)
    {
        vlc_tick_sleep( VLC_TICK_FROM_MS(wait_and_cancel) );
        libvlc_MetadataCancel(vlc->p_libvlc_int, vlc);

    }
    vlc_sem_wait(&sem);

    input_item_Release(p_item);
    vlc_sem_destroy(&sem);
    vlc_close(p_pipe[0]);
    vlc_close(p_pipe[1]);
}