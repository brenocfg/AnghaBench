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
typedef  int /*<<< orphan*/  optlist ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  const member_1; } ;
typedef  TYPE_1__ opt_t ;

/* Variables and functions */
#define  VLC_VAR_FLOAT 128 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 

__attribute__((used)) static const opt_t *
adjust_option_bynumber( unsigned option )
{
    static const opt_t optlist[] =
    {
        { "adjust",     0 },
        { "contrast",   VLC_VAR_FLOAT },
        { "brightness", VLC_VAR_FLOAT },
        { "hue",        VLC_VAR_FLOAT },
        { "saturation", VLC_VAR_FLOAT },
        { "gamma",      VLC_VAR_FLOAT },
    };
    enum { num_opts = sizeof(optlist) / sizeof(*optlist) };

    const opt_t *r = option < num_opts ? optlist+option : NULL;
    if( !r )
        libvlc_printerr( "Unknown adjust option" );
    return r;
}