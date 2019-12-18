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
typedef  int /*<<< orphan*/  vlc_video_context ;
struct vlc_va_t {int dummy; } ;
typedef  struct vlc_va_t vlc_va_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_decoder_device ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  es_format_t ;
typedef  int /*<<< orphan*/  AVPixFmtDescriptor ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_module_load (struct vlc_va_t*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct vlc_va_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 struct vlc_va_t* vlc_object_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_object_delete (struct vlc_va_t*) ; 
 int /*<<< orphan*/  vlc_va_Start ; 

vlc_va_t *vlc_va_New(vlc_object_t *obj,
                     AVCodecContext *avctx, const AVPixFmtDescriptor *src_desc,
                     const es_format_t *fmt_in, vlc_decoder_device *device,
                     video_format_t *fmt_out, vlc_video_context **vtcx_out)
{
    struct vlc_va_t *va = vlc_object_create(obj, sizeof (*va));
    if (unlikely(va == NULL))
        return NULL;


    if (vlc_module_load(va, "hw decoder", NULL, true,
                        vlc_va_Start, va, avctx, src_desc, fmt_in, device,
                        fmt_out, vtcx_out) == NULL)
    {
        vlc_object_delete(va);
        va = NULL;
    }

    return va;
}