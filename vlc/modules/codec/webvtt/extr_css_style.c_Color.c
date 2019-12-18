#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; scalar_t__* psz; TYPE_3__* function; } ;
typedef  TYPE_4__ vlc_css_term_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int i_count; TYPE_2__* seq; } ;
struct TYPE_6__ {int val; } ;
struct TYPE_7__ {TYPE_1__ term; } ;

/* Variables and functions */
 int STYLE_ALPHA_OPAQUE ; 
 scalar_t__ TYPE_FUNCTION ; 
 scalar_t__ TYPE_HEXCOLOR ; 
 scalar_t__ TYPE_IDENTIFIER ; 
 scalar_t__ TYPE_STRING ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,char*) ; 
 unsigned int vlc_html_color (scalar_t__*,int*) ; 

__attribute__((used)) static void Color( vlc_css_term_t term,
                   int *color, uint8_t *alpha,
                   uint16_t *feat, int cflag, int aflag )
{
    if( term.type == TYPE_FUNCTION )
    {
        if( term.function ) /* func( expr ) */
        {
            if( ( !strcmp( term.psz, "rgb" ) && term.function->i_count == 3 ) ||
                ( !strcmp( term.psz, "rgba" ) && term.function->i_count == 4 ) )
            {
                *color = (((int)term.function->seq[0].term.val) << 16) |
                         (((int)term.function->seq[1].term.val) << 8) |
                          ((int)term.function->seq[2].term.val);
                *feat |= cflag;
                if( term.psz[3] != 0 ) /* rgba */
                {
                    *alpha = term.function->seq[3].term.val * STYLE_ALPHA_OPAQUE;
                    *feat |= aflag;
                }
            }
        }
    }
    else if( term.type == TYPE_STRING ||
             term.type == TYPE_HEXCOLOR ||
             term.type == TYPE_IDENTIFIER )
    {
        bool b_valid = false;
        unsigned i_color = vlc_html_color( term.psz, &b_valid );
        if( b_valid )
        {
            *alpha = (i_color & 0xFF000000) >> 24;
            *color = i_color & 0x00FFFFFF;
            *feat |= cflag|aflag;
        }
    }
}