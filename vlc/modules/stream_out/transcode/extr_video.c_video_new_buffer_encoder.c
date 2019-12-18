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
typedef  int /*<<< orphan*/  transcode_encoder_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_2__ {int /*<<< orphan*/  video; } ;

/* Variables and functions */
 int /*<<< orphan*/ * picture_NewFromFormat (int /*<<< orphan*/ *) ; 
 TYPE_1__* transcode_encoder_format_in (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *video_new_buffer_encoder( transcode_encoder_t *p_enc )
{
    return picture_NewFromFormat( &transcode_encoder_format_in( p_enc )->video );
}