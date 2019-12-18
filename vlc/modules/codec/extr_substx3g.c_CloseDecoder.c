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
typedef  int /*<<< orphan*/  text_style_t ;
struct TYPE_2__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CloseDecoder( vlc_object_t *p_this )
{
    decoder_t     *p_dec = (decoder_t *) p_this;
    text_style_Delete( (text_style_t *) p_dec->p_sys );
}