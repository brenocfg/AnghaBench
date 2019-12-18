#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ i_cat; } ;
struct TYPE_10__ {TYPE_3__* cbs; TYPE_1__ fmt_in; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* abort_pictures ) (TYPE_4__*,int) ;} ;
struct TYPE_9__ {TYPE_2__ video; } ;

/* Variables and functions */
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  vlc_assert (int /*<<< orphan*/ ) ; 

void decoder_AbortPictures(decoder_t *dec, bool abort)
{
    vlc_assert(dec->fmt_in.i_cat == VIDEO_ES && dec->cbs);
    if (dec->cbs->video.abort_pictures)
        dec->cbs->video.abort_pictures(dec, abort);
}