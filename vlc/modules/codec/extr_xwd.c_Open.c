#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_6__ {scalar_t__ i_codec; } ;
struct TYPE_4__ {TYPE_2__ fmt_out; TYPE_3__ fmt_in; int /*<<< orphan*/  pf_decode; } ;
typedef  TYPE_1__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  Decode ; 
 int /*<<< orphan*/  VLC_CODEC_RGB32 ; 
 scalar_t__ VLC_CODEC_XWD ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    decoder_t *dec = (decoder_t *)obj;

    if (dec->fmt_in.i_codec != VLC_CODEC_XWD)
        return VLC_EGENERIC;

    dec->pf_decode = Decode;
    es_format_Copy(&dec->fmt_out, &dec->fmt_in);
    dec->fmt_out.i_codec = VLC_CODEC_RGB32;
    return VLC_SUCCESS;
}