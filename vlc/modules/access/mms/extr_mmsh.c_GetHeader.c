#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_9__ {int i_type; scalar_t__ i_data; int /*<<< orphan*/  p_data; scalar_t__ i_size; } ;
typedef  TYPE_2__ chunk_t ;
struct TYPE_10__ {scalar_t__ i_header; int /*<<< orphan*/ * p_header; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 scalar_t__ GetPacket (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/ * xrealloc (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void GetHeader( stream_t *p_access, int i_content_length )
{
    access_sys_t *p_sys = p_access->p_sys;
    int i_read_content = 0;

    /* Read the asf header */
    p_sys->i_header = 0;
    free( p_sys->p_header  );
    p_sys->p_header = NULL;
    for( ;; )
    {
        chunk_t ck;
        if( (i_content_length >= 0 && i_read_content >= i_content_length) || GetPacket( p_access, &ck ) || ck.i_type != 0x4824 )
            break;

        i_read_content += (4+ck.i_size);

        if( ck.i_data > 0 )
        {
            p_sys->i_header += ck.i_data;
            p_sys->p_header = xrealloc( p_sys->p_header, p_sys->i_header );
            memcpy( &p_sys->p_header[p_sys->i_header - ck.i_data],
                    ck.p_data, ck.i_data );
        }
    }
    msg_Dbg( p_access, "complete header size=%d", p_sys->i_header );
}