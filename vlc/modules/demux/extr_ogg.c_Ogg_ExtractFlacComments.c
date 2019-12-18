#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  es_format_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 unsigned int GetDW24BE (int const*) ; 
 int /*<<< orphan*/  Ogg_ExtractComments (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const*,unsigned int) ; 

__attribute__((used)) static void Ogg_ExtractFlacComments( demux_t *p_demux, es_format_t *p_fmt,
                                     const uint8_t *p_headers, unsigned i_headers )
{
    /* Skip Streaminfo 42 bytes / 1st page */
    if(i_headers <= 46)
        return;
    p_headers += 42; i_headers -= 42;
    /* Block Header 1 + 3 bytes */
    uint32_t blocksize = GetDW24BE(&p_headers[1]);
    if(p_headers[0] == 0x84 && blocksize <= i_headers - 4)
    {
        Ogg_ExtractComments( p_demux, p_fmt, &p_headers[4], i_headers - 4 );
    }
}