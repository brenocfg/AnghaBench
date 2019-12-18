#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int /*<<< orphan*/  tcx; int /*<<< orphan*/  tc; int /*<<< orphan*/  ti; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  th_comment_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  th_decode_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  th_info_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CloseDecoder( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t *)p_this;
    decoder_sys_t *p_sys = p_dec->p_sys;

    th_info_clear(&p_sys->ti);
    th_comment_clear(&p_sys->tc);
    th_decode_free(p_sys->tcx);
    free( p_sys );
}