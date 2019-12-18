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
typedef  int /*<<< orphan*/  vlogo_optlist ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  const member_1; } ;
typedef  TYPE_1__ opt_t ;

/* Variables and functions */
#define  VLC_VAR_INTEGER 129 
#define  VLC_VAR_STRING 128 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 

__attribute__((used)) static const opt_t *
logo_option_bynumber( unsigned option )
{
    static const opt_t vlogo_optlist[] =
    /* depends on libvlc_video_logo_option_t */
    {
        { "logo",          0 },
        { "logo-file",     VLC_VAR_STRING },
        { "logo-x",        VLC_VAR_INTEGER },
        { "logo-y",        VLC_VAR_INTEGER },
        { "logo-delay",    VLC_VAR_INTEGER },
        { "logo-repeat",   VLC_VAR_INTEGER },
        { "logo-opacity",  VLC_VAR_INTEGER },
        { "logo-position", VLC_VAR_INTEGER },
    };
    enum { num_vlogo_opts = sizeof(vlogo_optlist) / sizeof(*vlogo_optlist) };

    const opt_t *r = option < num_vlogo_opts ? vlogo_optlist+option : NULL;
    if( !r )
        libvlc_printerr( "Unknown logo option" );
    return r;
}