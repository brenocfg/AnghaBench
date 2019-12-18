#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  psz_line ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_6__ {int /*<<< orphan*/ * ppsz_lines; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  decode_string (char*,int,TYPE_2__*,int,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool DecodePacketX25( decoder_t *p_dec, const uint8_t *packet,
                             int magazine )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    /* row 25 : alternate header line */
    char psz_line[256];
    decode_string( psz_line, sizeof(psz_line), p_sys, magazine,
                   packet + 6, 40 );

    /* replace the row if it's different */
    if ( strcmp( psz_line, p_sys->ppsz_lines[0] ) )
    {
        strncpy( p_sys->ppsz_lines[0], psz_line,
                 sizeof(p_sys->ppsz_lines[0]) - 1 );
        /* return true; */
    }

    return false;
}