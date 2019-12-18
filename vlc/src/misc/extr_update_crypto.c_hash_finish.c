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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/ * hashed_data; int /*<<< orphan*/ * hashed_data_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_8__ {TYPE_2__ v4; TYPE_1__ v3; } ;
struct TYPE_9__ {int version; size_t type; size_t public_key_algo; size_t digest_algo; TYPE_3__ specific; } ;
typedef  TYPE_4__ signature_packet_t ;
typedef  size_t i_len ;
typedef  int /*<<< orphan*/  gcry_md_hd_t ;

/* Variables and functions */
 int /*<<< orphan*/  gcry_md_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_final (int /*<<< orphan*/ ) ; 
 unsigned int gcry_md_get_algo_dlen (size_t) ; 
 int /*<<< orphan*/  gcry_md_putc (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ gcry_md_read (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gcry_md_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 size_t scalar_number (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint8_t *hash_finish( gcry_md_hd_t hd, signature_packet_t *p_sig )
{
    if( p_sig->version == 3 )
    {
        gcry_md_putc( hd, p_sig->type );
        gcry_md_write( hd, &p_sig->specific.v3.timestamp, 4 );
    }
    else if( p_sig->version == 4 )
    {
        gcry_md_putc( hd, p_sig->version );
        gcry_md_putc( hd, p_sig->type );
        gcry_md_putc( hd, p_sig->public_key_algo );
        gcry_md_putc( hd, p_sig->digest_algo );
        gcry_md_write( hd, p_sig->specific.v4.hashed_data_len, 2 );
        size_t i_len = scalar_number( p_sig->specific.v4.hashed_data_len, 2 );
        gcry_md_write( hd, p_sig->specific.v4.hashed_data, i_len );

        gcry_md_putc( hd, 0x04 );
        gcry_md_putc( hd, 0xFF );

        i_len += 6; /* hashed data + 6 bytes header */

        gcry_md_putc( hd, (i_len >> 24) & 0xff );
        gcry_md_putc( hd, (i_len >> 16) & 0xff );
        gcry_md_putc( hd, (i_len >> 8) & 0xff );
        gcry_md_putc( hd, (i_len) & 0xff );
    }
    else
    {   /* RFC 4880 only tells about versions 3 and 4 */
        return NULL;
    }

    gcry_md_final( hd );

    uint8_t *p_tmp = (uint8_t*) gcry_md_read( hd, p_sig->digest_algo) ;
    unsigned int hash_len = gcry_md_get_algo_dlen (p_sig->digest_algo);
    uint8_t *p_hash = malloc(hash_len);
    if( p_hash )
        memcpy(p_hash, p_tmp, hash_len);
    gcry_md_close( hd );
    return p_hash;
}