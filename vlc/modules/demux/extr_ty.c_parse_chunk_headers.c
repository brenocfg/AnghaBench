#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int rec_type; int subrec_type; int* ex; int l_rec_size; int b_ext; int /*<<< orphan*/  l_ty_pts; } ;
typedef  TYPE_1__ ty_rec_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  U64_AT (int const*) ; 
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static ty_rec_hdr_t *parse_chunk_headers( const uint8_t *p_buf,
                                          int i_num_recs, int *pi_payload_size)
{
    int i;
    ty_rec_hdr_t *p_hdrs, *p_rec_hdr;

    *pi_payload_size = 0;
    p_hdrs = xmalloc(i_num_recs * sizeof(ty_rec_hdr_t));

    for (i = 0; i < i_num_recs; i++)
    {
        const uint8_t *record_header = p_buf + (i * 16);
        p_rec_hdr = &p_hdrs[i];     /* for brevity */
        p_rec_hdr->rec_type = record_header[3];
        p_rec_hdr->subrec_type = record_header[2] & 0x0f;
        if ((record_header[ 0 ] & 0x80) == 0x80)
        {
            uint8_t b1, b2;
            /* marker bit 2 set, so read extended data */
            b1 = ( ( ( record_header[ 0 ] & 0x0f ) << 4 ) |
                   ( ( record_header[ 1 ] & 0xf0 ) >> 4 ) );
            b2 = ( ( ( record_header[ 1 ] & 0x0f ) << 4 ) |
                   ( ( record_header[ 2 ] & 0xf0 ) >> 4 ) );

            p_rec_hdr->ex[0] = b1;
            p_rec_hdr->ex[1] = b2;
            p_rec_hdr->l_rec_size = 0;
            p_rec_hdr->l_ty_pts = 0;
            p_rec_hdr->b_ext = true;
        }
        else
        {
            p_rec_hdr->l_rec_size = ( record_header[ 0 ] << 8 |
                record_header[ 1 ] ) << 4 | ( record_header[ 2 ] >> 4 );
            *pi_payload_size += p_rec_hdr->l_rec_size;
            p_rec_hdr->b_ext = false;
            p_rec_hdr->l_ty_pts = U64_AT( &record_header[ 8 ] );
        }
        //fprintf( stderr, "parse_chunk_headers[%d] t=0x%x s=%d\n", i, p_rec_hdr->rec_type, p_rec_hdr->subrec_type );
    } /* end of record-header loop */
    return p_hdrs;
}