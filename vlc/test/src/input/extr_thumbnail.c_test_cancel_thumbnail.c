#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_thumbnailer_t ;
typedef  int /*<<< orphan*/  vlc_thumbnailer_request_t ;
struct test_ctx {int b_done; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_THUMBNAILER_SEEK_PRECISE ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * input_item_New (char const*,char*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thumbnailer_callback_cancel ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int vlc_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_thumbnailer_Cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_thumbnailer_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_thumbnailer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_thumbnailer_RequestByTime (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct test_ctx*) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void test_cancel_thumbnail( libvlc_instance_t* p_vlc )
{
    vlc_thumbnailer_t* p_thumbnailer = vlc_thumbnailer_Create(
                VLC_OBJECT( p_vlc->p_libvlc_int ) );
    assert( p_thumbnailer != NULL );

    struct test_ctx ctx;
    vlc_cond_init( &ctx.cond );
    vlc_mutex_init( &ctx.lock );

    const char* psz_mrl = "mock://video_track_count=1;audio_track_count=1";
    input_item_t* p_item = input_item_New( psz_mrl, "mock item" );
    assert( p_item != NULL );

    vlc_mutex_lock( &ctx.lock );
    int res = 0;
    vlc_thumbnailer_request_t* p_req = vlc_thumbnailer_RequestByTime( p_thumbnailer,
        VLC_TICK_FROM_SEC( 1 ), VLC_THUMBNAILER_SEEK_PRECISE, p_item,
        VLC_TICK_INVALID, thumbnailer_callback_cancel, &ctx );
    vlc_thumbnailer_Cancel( p_thumbnailer, p_req );
    while ( ctx.b_done == false )
    {
        vlc_tick_t timeout = vlc_tick_now() + VLC_TICK_FROM_SEC( 1 );
        res = vlc_cond_timedwait( &ctx.cond, &ctx.lock, timeout );
        assert( res != ETIMEDOUT );
    }
    vlc_mutex_unlock( &ctx.lock );

    input_item_Release( p_item );

    vlc_thumbnailer_Release( p_thumbnailer );
}