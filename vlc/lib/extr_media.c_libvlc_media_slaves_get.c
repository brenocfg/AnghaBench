#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {TYPE_3__* p_input_item; } ;
typedef  TYPE_1__ libvlc_media_t ;
struct TYPE_11__ {char* psz_uri; int i_priority; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_2__ libvlc_media_slave_t ;
struct TYPE_12__ {int i_slaves; int /*<<< orphan*/  lock; TYPE_4__** pp_slaves; } ;
typedef  TYPE_3__ input_item_t ;
struct TYPE_13__ {int i_priority; int i_type; int /*<<< orphan*/  psz_uri; } ;
typedef  TYPE_4__ input_item_slave_t ;

/* Variables and functions */
#define  SLAVE_PRIORITY_MATCH_ALL 134 
#define  SLAVE_PRIORITY_MATCH_LEFT 133 
#define  SLAVE_PRIORITY_MATCH_NONE 132 
#define  SLAVE_PRIORITY_MATCH_RIGHT 131 
#define  SLAVE_PRIORITY_USER 130 
#define  SLAVE_TYPE_AUDIO 129 
#define  SLAVE_TYPE_SPU 128 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__** calloc (int,int) ; 
 int /*<<< orphan*/  libvlc_media_slave_type_audio ; 
 int /*<<< orphan*/  libvlc_media_slave_type_subtitle ; 
 int /*<<< orphan*/  libvlc_media_slaves_release (TYPE_2__**,int) ; 
 TYPE_2__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 unsigned int vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

unsigned int libvlc_media_slaves_get( libvlc_media_t *p_md,
                                      libvlc_media_slave_t ***ppp_slaves )
{
    assert( p_md && ppp_slaves );
    input_item_t *p_input_item = p_md->p_input_item;
    *ppp_slaves = NULL;

    vlc_mutex_lock( &p_input_item->lock );

    int i_count = p_input_item->i_slaves;
    if( i_count <= 0 )
        return vlc_mutex_unlock( &p_input_item->lock ), 0;

    libvlc_media_slave_t **pp_slaves = calloc( i_count, sizeof(*pp_slaves) );
    if( pp_slaves == NULL )
        return vlc_mutex_unlock( &p_input_item->lock ), 0;

    for( int i = 0; i < i_count; ++i )
    {
        input_item_slave_t *p_item_slave = p_input_item->pp_slaves[i];
        assert( p_item_slave->i_priority >= SLAVE_PRIORITY_MATCH_NONE );

        /* also allocate psz_uri buffer at the end of the struct */
        libvlc_media_slave_t *p_slave = malloc( sizeof(*p_slave) +
                                                strlen( p_item_slave->psz_uri )
                                                + 1 );
        if( p_slave == NULL )
        {
            libvlc_media_slaves_release(pp_slaves, i);
            return vlc_mutex_unlock( &p_input_item->lock ), 0;
        }
        p_slave->psz_uri = (char *) ((uint8_t *)p_slave) + sizeof(*p_slave);
        strcpy( p_slave->psz_uri, p_item_slave->psz_uri );

        switch( p_item_slave->i_type )
        {
        case SLAVE_TYPE_SPU:
            p_slave->i_type = libvlc_media_slave_type_subtitle;
            break;
        case SLAVE_TYPE_AUDIO:
            p_slave->i_type = libvlc_media_slave_type_audio;
            break;
        default:
            vlc_assert_unreachable();
        }

        switch( p_item_slave->i_priority )
        {
        case SLAVE_PRIORITY_MATCH_NONE:
            p_slave->i_priority = 0;
            break;
        case SLAVE_PRIORITY_MATCH_RIGHT:
            p_slave->i_priority = 1;
            break;
        case SLAVE_PRIORITY_MATCH_LEFT:
            p_slave->i_priority = 2;
            break;
        case SLAVE_PRIORITY_MATCH_ALL:
            p_slave->i_priority = 3;
            break;
        case SLAVE_PRIORITY_USER:
            p_slave->i_priority = 4;
            break;
        default:
            vlc_assert_unreachable();
        }
        pp_slaves[i] = p_slave;
    }
    vlc_mutex_unlock( &p_input_item->lock );

    *ppp_slaves = pp_slaves;
    return i_count;
}