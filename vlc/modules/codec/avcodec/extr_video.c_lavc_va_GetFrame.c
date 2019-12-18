#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_va_t ;
struct AVCodecContext {TYPE_1__* opaque; } ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_8__ {int /*<<< orphan*/ * p_va; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/ * opaque; int /*<<< orphan*/ ** data; int /*<<< orphan*/ ** buf; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_buffer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * decoder_NewPicture (TYPE_1__*) ; 
 int /*<<< orphan*/  lavc_ReleaseFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_va_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int lavc_va_GetFrame(struct AVCodecContext *ctx, AVFrame *frame)
{
    decoder_t *dec = ctx->opaque;
    decoder_sys_t *p_sys = dec->p_sys;
    vlc_va_t *va = p_sys->p_va;

    picture_t *pic;
    pic = decoder_NewPicture(dec);
    if (pic == NULL)
        return -1;

    if (vlc_va_Get(va, pic, &frame->data[0]))
    {
        msg_Err(dec, "hardware acceleration picture allocation failed");
        picture_Release(pic);
        return -1;
    }
    assert(frame->data[0] != NULL);
    /* data[0] must be non-NULL for libavcodec internal checks.
     * data[3] actually contains the format-specific surface handle. */
    frame->data[3] = frame->data[0];

    frame->buf[0] = av_buffer_create(frame->data[0], 0, lavc_ReleaseFrame, pic, 0);
    if (unlikely(frame->buf[0] == NULL))
    {
        lavc_ReleaseFrame(pic, frame->data[0]);
        return -1;
    }

    frame->opaque = pic;
    return 0;
}