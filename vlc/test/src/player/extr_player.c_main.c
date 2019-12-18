#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ctx {TYPE_1__* vlc; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_libvlc_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_destroy (struct ctx*) ; 
 int /*<<< orphan*/  ctx_init (struct ctx*,int) ; 
 int /*<<< orphan*/  test_capabilities_pause (struct ctx*) ; 
 int /*<<< orphan*/  test_capabilities_seek (struct ctx*) ; 
 int /*<<< orphan*/  test_delete_while_playback (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_error (struct ctx*) ; 
 int /*<<< orphan*/  test_init () ; 
 int /*<<< orphan*/  test_next_media (struct ctx*) ; 
 int /*<<< orphan*/  test_no_outputs (struct ctx*) ; 
 int /*<<< orphan*/  test_outputs (struct ctx*) ; 
 int /*<<< orphan*/  test_pause (struct ctx*) ; 
 int /*<<< orphan*/  test_programs (struct ctx*) ; 
 int /*<<< orphan*/  test_seeks (struct ctx*) ; 
 int /*<<< orphan*/  test_set_current_media (struct ctx*) ; 
 int /*<<< orphan*/  test_timers (struct ctx*) ; 
 int /*<<< orphan*/  test_titles (struct ctx*,int) ; 
 int /*<<< orphan*/  test_tracks (struct ctx*,int) ; 
 int /*<<< orphan*/  test_unknown_uri (struct ctx*) ; 

int
main(void)
{
    test_init();

    struct ctx ctx;

    /* Test with --aout=none --vout=none */
    ctx_init(&ctx, false);
    test_no_outputs(&ctx);
    ctx_destroy(&ctx);
    ctx_init(&ctx, true);

    test_outputs(&ctx); /* Must be the first test */

    test_set_current_media(&ctx);
    test_next_media(&ctx);
    test_seeks(&ctx);
    test_pause(&ctx);
    test_capabilities_pause(&ctx);
    test_capabilities_seek(&ctx);
    test_error(&ctx);
    test_unknown_uri(&ctx);
    test_titles(&ctx, true);
    test_titles(&ctx, false);
    test_tracks(&ctx, true);
    test_tracks(&ctx, false);
    test_programs(&ctx);
    test_timers(&ctx);

    test_delete_while_playback(VLC_OBJECT(ctx.vlc->p_libvlc_int), true);
    test_delete_while_playback(VLC_OBJECT(ctx.vlc->p_libvlc_int), false);

    ctx_destroy(&ctx);
    return 0;
}