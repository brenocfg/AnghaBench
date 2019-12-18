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
typedef  char uint8_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int i_data_peeked; char* p_peek; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Peek (TYPE_1__*,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char* GetLine( demux_t *p_demux, int *p_pos )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    const uint8_t *p_buf;
    int         i_size;
    int         i;
    char        *p_line;

    while( *p_pos >= p_sys->i_data_peeked )
    {
        if( ! Peek( p_demux, false ) )
        {
            return NULL;
        }
    }
    p_buf = p_sys->p_peek + *p_pos;
    i_size = p_sys->i_data_peeked - *p_pos;
    i = 0;
    while( p_buf[i] != '\n' )
    {
        i++;
        if( i == i_size )
        {
            if( ! Peek( p_demux, false ) )
            {
                return NULL;
            }
            p_buf = p_sys->p_peek + *p_pos;
            i_size = p_sys->i_data_peeked - *p_pos;
        }
    }
    *p_pos += i + 1;
    if( i > 0 && p_buf[i - 1] == '\r' )
    {
        i--;
    }
    p_line = malloc( i + 1 );
    if( unlikely( p_line == NULL ) )
        return NULL;
    strncpy ( p_line, (char*)p_buf, i );
    p_line[i] = '\0';
    return p_line;
}