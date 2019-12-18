#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * p_description; int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  fmt_in; int /*<<< orphan*/ * p_module; } ;
typedef  TYPE_1__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 

void decoder_Clean( decoder_t *p_dec )
{
    if ( p_dec->p_module != NULL )
    {
        module_unneed(p_dec, p_dec->p_module);
        p_dec->p_module = NULL;
    }

    es_format_Clean( &p_dec->fmt_in );
    es_format_Clean( &p_dec->fmt_out );

    if ( p_dec->p_description )
    {
        vlc_meta_Delete(p_dec->p_description);
        p_dec->p_description = NULL;
    }
}