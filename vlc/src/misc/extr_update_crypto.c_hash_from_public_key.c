#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_13__ {int version; scalar_t__ type; scalar_t__* hash_verification; int /*<<< orphan*/  digest_algo; } ;
struct TYPE_9__ {int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  g; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
struct TYPE_10__ {TYPE_2__ rsa; TYPE_1__ dsa; } ;
struct TYPE_11__ {scalar_t__ algo; size_t version; scalar_t__* timestamp; TYPE_3__ sig; } ;
struct TYPE_12__ {scalar_t__* psz_username; TYPE_7__ sig; TYPE_4__ key; } ;
typedef  TYPE_5__ public_key_t ;
typedef  size_t i_len ;
typedef  int /*<<< orphan*/  gcry_md_hd_t ;
typedef  scalar_t__ gcry_error_t ;

/* Variables and functions */
 scalar_t__ const GCRY_PK_DSA ; 
 scalar_t__ const GCRY_PK_RSA ; 
 scalar_t__ GENERIC_KEY_SIGNATURE ; 
 scalar_t__ POSITIVE_KEY_SIGNATURE ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ gcry_md_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_putc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gcry_md_write (int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 scalar_t__* hash_finish (int /*<<< orphan*/ ,TYPE_7__*) ; 
 size_t mpi_len (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

uint8_t *hash_from_public_key( public_key_t *p_pkey )
{
    const uint8_t pk_algo = p_pkey->key.algo;
    size_t i_size;
    size_t i_p_len, i_g_len, i_q_len, i_y_len;
    size_t i_n_len, i_e_len;

    if( p_pkey->sig.version != 4 )
        return NULL;

    if( p_pkey->sig.type < GENERIC_KEY_SIGNATURE ||
        p_pkey->sig.type > POSITIVE_KEY_SIGNATURE )
        return NULL;

    if( p_pkey->psz_username == NULL )
        return NULL;

    gcry_error_t error = 0;
    gcry_md_hd_t hd;

    if (pk_algo == GCRY_PK_DSA) {
        i_p_len = mpi_len( p_pkey->key.sig.dsa.p );
        i_g_len = mpi_len( p_pkey->key.sig.dsa.g );
        i_q_len = mpi_len( p_pkey->key.sig.dsa.q );
        i_y_len = mpi_len( p_pkey->key.sig.dsa.y );

        i_size = 6 + 2*4 + i_p_len + i_g_len + i_q_len + i_y_len;
    } else if (pk_algo == GCRY_PK_RSA) {
        i_n_len = mpi_len( p_pkey->key.sig.rsa.n );
        i_e_len = mpi_len( p_pkey->key.sig.rsa.e );

        i_size = 6 + 2*2 + i_n_len + i_e_len;
    } else
        return NULL;

    error = gcry_md_open( &hd, p_pkey->sig.digest_algo, 0 );
    if( error )
        return NULL;

    gcry_md_putc( hd, 0x99 );

    gcry_md_putc( hd, (i_size >> 8) & 0xff );
    gcry_md_putc( hd, i_size & 0xff );

    gcry_md_putc( hd, p_pkey->key.version );
    gcry_md_write( hd, p_pkey->key.timestamp, 4 );
    gcry_md_putc( hd, p_pkey->key.algo );

    if (pk_algo == GCRY_PK_DSA) {
        gcry_md_write( hd, (uint8_t*)&p_pkey->key.sig.dsa.p, 2 + i_p_len );
        gcry_md_write( hd, (uint8_t*)&p_pkey->key.sig.dsa.q, 2 + i_q_len );
        gcry_md_write( hd, (uint8_t*)&p_pkey->key.sig.dsa.g, 2 + i_g_len );
        gcry_md_write( hd, (uint8_t*)&p_pkey->key.sig.dsa.y, 2 + i_y_len );
    } else if (pk_algo == GCRY_PK_RSA) {
        gcry_md_write( hd, (uint8_t*)&p_pkey->key.sig.rsa.n, 2 + i_n_len );
        gcry_md_write( hd, (uint8_t*)&p_pkey->key.sig.rsa.e, 2 + i_e_len );
    }

    gcry_md_putc( hd, 0xb4 );

    size_t i_len = strlen((char*)p_pkey->psz_username);

    gcry_md_putc( hd, (i_len >> 24) & 0xff );
    gcry_md_putc( hd, (i_len >> 16) & 0xff );
    gcry_md_putc( hd, (i_len >> 8) & 0xff );
    gcry_md_putc( hd, (i_len) & 0xff );

    gcry_md_write( hd, p_pkey->psz_username, i_len );

    uint8_t *p_hash = hash_finish( hd, &p_pkey->sig );
    if( !p_hash ||
        p_hash[0] != p_pkey->sig.hash_verification[0] ||
        p_hash[1] != p_pkey->sig.hash_verification[1] )
    {
        free(p_hash);
        return NULL;
    }

    return p_hash;
}