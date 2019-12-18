#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pf_update_progress; int /*<<< orphan*/  pf_cancel; int /*<<< orphan*/  pf_display_progress; int /*<<< orphan*/  pf_display_question; int /*<<< orphan*/  pf_display_login; int /*<<< orphan*/  pf_display_error; } ;
typedef  TYPE_1__ vlc_dialog_cbs ;
struct cb_answer {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  p_libvlc_int; } ;
typedef  TYPE_2__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cancel_cb ; 
 int /*<<< orphan*/  display_error_cb ; 
 int /*<<< orphan*/  display_login_cb ; 
 int /*<<< orphan*/  display_progress_cb ; 
 int /*<<< orphan*/  display_question_cb ; 
 int libvlc_InternalAddIntf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_dialogs (int /*<<< orphan*/ ,struct cb_answer*,int) ; 
 int /*<<< orphan*/  update_progress_cb ; 
 int /*<<< orphan*/  vlc_dialog_provider_set_callbacks (int /*<<< orphan*/ ,TYPE_1__ const*,struct cb_answer*) ; 

int
main(int i_argc, char *ppsz_argv[])
{
    bool b_test_all = i_argc > 1 && strcmp(ppsz_argv[1], "-a") == 0;

    if (!b_test_all)
        alarm(10);

    setenv("VLC_PLUGIN_PATH", "../modules", 1);
    setenv("VLC_LIB_PATH", "../modules", 1);

    libvlc_instance_t *p_libvlc = libvlc_new(0, NULL);
    assert(p_libvlc != NULL);

    printf("testing dialog callbacks\n");
    const vlc_dialog_cbs cbs = {
        .pf_display_error = display_error_cb,
        .pf_display_login = display_login_cb,
        .pf_display_question = display_question_cb,
        .pf_display_progress = display_progress_cb,
        .pf_cancel = cancel_cb,
        .pf_update_progress = update_progress_cb,
    };
    struct cb_answer ans = { 0 };
    vlc_dialog_provider_set_callbacks(p_libvlc->p_libvlc_int, &cbs, &ans);
    test_dialogs(VLC_OBJECT(p_libvlc->p_libvlc_int), &ans, 100000);
    vlc_dialog_provider_set_callbacks(p_libvlc->p_libvlc_int, NULL, NULL);

    libvlc_release(p_libvlc);

    if (b_test_all)
    {
        printf("testing Qt dialog callbacks\n");
        static const char *args[] = {
            "--no-qt-privacy-ask", /* avoid dialog that ask for privacy */
        };
        p_libvlc = libvlc_new(1, args);
        assert(p_libvlc != NULL);

        int i_ret = libvlc_InternalAddIntf(p_libvlc->p_libvlc_int, "qt");
        assert(i_ret == VLC_SUCCESS);
        test_dialogs(VLC_OBJECT(p_libvlc->p_libvlc_int), NULL, 3000000);

        libvlc_release(p_libvlc);
    }

    return 0;
}