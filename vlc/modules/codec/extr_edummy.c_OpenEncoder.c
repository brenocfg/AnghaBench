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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {int /*<<< orphan*/  pf_encode_audio; int /*<<< orphan*/  pf_encode_video; } ;
typedef  TYPE_1__ encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  EncodeAudio ; 
 int /*<<< orphan*/  EncodeVideo ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int OpenEncoder( vlc_object_t *p_this )
{
    encoder_t *p_enc = (encoder_t *)p_this;

    p_enc->pf_encode_video = EncodeVideo;
    p_enc->pf_encode_audio = EncodeAudio;

    return VLC_SUCCESS;
}