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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_9__ {scalar_t__* psz_value; int /*<<< orphan*/  i_namespace; } ;
struct TYPE_7__ {TYPE_1__* p_keys; } ;
struct TYPE_8__ {TYPE_2__ data; } ;
struct TYPE_6__ {int i_entry_count; TYPE_4__* p_entries; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_keys_t ; 
 int /*<<< orphan*/  MP4_FreeBox_keys ; 
 int /*<<< orphan*/  MP4_GET4BYTES (int) ; 
 int /*<<< orphan*/  MP4_GETFOURCC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 TYPE_4__* calloc (int,int) ; 
 int i_read ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int,scalar_t__*) ; 
 int p_peek ; 

__attribute__((used)) static int MP4_ReadBox_keys( stream_t *p_stream, MP4_Box_t *p_box )
{
    MP4_READBOX_ENTER( MP4_Box_data_keys_t, MP4_FreeBox_keys );

    if ( i_read < 8 )
        MP4_READBOX_EXIT( 0 );

    uint32_t i_count;
    MP4_GET4BYTES( i_count ); /* reserved + flags */
    if ( i_count != 0 )
        MP4_READBOX_EXIT( 0 );

    MP4_GET4BYTES( i_count );
    p_box->data.p_keys->p_entries = calloc( i_count, sizeof(*p_box->data.p_keys->p_entries) );
    if ( !p_box->data.p_keys->p_entries )
        MP4_READBOX_EXIT( 0 );
    p_box->data.p_keys->i_entry_count = i_count;

    uint32_t i=0;
    for( ; i < i_count; i++ )
    {
        if ( i_read < 8 )
            break;
        uint32_t i_keysize;
        MP4_GET4BYTES( i_keysize );
        if ( (i_keysize < 8) || (i_keysize - 4 > i_read) )
            break;
        MP4_GETFOURCC( p_box->data.p_keys->p_entries[i].i_namespace );
        i_keysize -= 8;
        p_box->data.p_keys->p_entries[i].psz_value = malloc( i_keysize + 1 );
        if ( !p_box->data.p_keys->p_entries[i].psz_value )
            break;
        memcpy( p_box->data.p_keys->p_entries[i].psz_value, p_peek, i_keysize );
        p_box->data.p_keys->p_entries[i].psz_value[i_keysize] = 0;
        p_peek += i_keysize;
        i_read -= i_keysize;
#ifdef MP4_ULTRA_VERBOSE
        msg_Dbg( p_stream, "read box: \"keys\": %u '%s'", i + 1,
                 p_box->data.p_keys->p_entries[i].psz_value );
#endif
    }
    if ( i < i_count )
        p_box->data.p_keys->i_entry_count = i;

    MP4_READBOX_EXIT( 1 );
}