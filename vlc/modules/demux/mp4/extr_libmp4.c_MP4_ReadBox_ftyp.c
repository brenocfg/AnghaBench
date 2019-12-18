#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {TYPE_1__* p_ftyp; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
struct TYPE_5__ {int i_compatible_brands_count; int /*<<< orphan*/ * i_compatible_brands; int /*<<< orphan*/  i_minor_version; int /*<<< orphan*/  i_major_brand; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_ftyp_t ; 
 int /*<<< orphan*/  MP4_FreeBox_ftyp ; 
 int /*<<< orphan*/  MP4_GET4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GETFOURCC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 int i_read ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_alloc (int,int) ; 

__attribute__((used)) static int MP4_ReadBox_ftyp( stream_t *p_stream, MP4_Box_t *p_box )
{
    MP4_READBOX_ENTER( MP4_Box_data_ftyp_t, MP4_FreeBox_ftyp );

    MP4_GETFOURCC( p_box->data.p_ftyp->i_major_brand );
    MP4_GET4BYTES( p_box->data.p_ftyp->i_minor_version );

    p_box->data.p_ftyp->i_compatible_brands_count = i_read / 4;
    if( p_box->data.p_ftyp->i_compatible_brands_count > 0 )
    {
        uint32_t *tab = p_box->data.p_ftyp->i_compatible_brands =
            vlc_alloc( p_box->data.p_ftyp->i_compatible_brands_count,
                       sizeof(uint32_t) );

        if( unlikely( tab == NULL ) )
            MP4_READBOX_EXIT( 0 );

        for( unsigned i = 0; i < p_box->data.p_ftyp->i_compatible_brands_count; i++ )
        {
            MP4_GETFOURCC( tab[i] );
        }
    }
    else
    {
        p_box->data.p_ftyp->i_compatible_brands = NULL;
    }

    MP4_READBOX_EXIT( 1 );
}