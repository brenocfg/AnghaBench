#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/ * s; int /*<<< orphan*/ * r; } ;
struct TYPE_12__ {TYPE_3__ dsa; } ;
struct TYPE_13__ {int /*<<< orphan*/  digest_algo; TYPE_4__ algo_specific; } ;
typedef  TYPE_5__ signature_packet_t ;
struct TYPE_9__ {int /*<<< orphan*/ * y; int /*<<< orphan*/ * g; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
struct TYPE_10__ {TYPE_1__ dsa; } ;
struct TYPE_14__ {TYPE_2__ sig; } ;
typedef  TYPE_6__ public_key_packet_t ;
typedef  int /*<<< orphan*/ * gcry_sexp_t ;
typedef  int /*<<< orphan*/ * gcry_mpi_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCRYMPI_FMT_USG ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int gcry_md_get_algo_dlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_release (int /*<<< orphan*/ *) ; 
 scalar_t__ gcry_mpi_scan (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ gcry_pk_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gcry_sexp_build (int /*<<< orphan*/ **,size_t*,char const*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  gcry_sexp_release (int /*<<< orphan*/ *) ; 
 int mpi_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int verify_signature_dsa( signature_packet_t *sign, public_key_packet_t *p_key,
                      uint8_t *p_hash )
{
    int ret = VLC_EGENERIC;

    /* the data to be verified (a hash) */
    const char *hash_sexp_s = "(data(flags raw)(value %m))";
    /* the public key */
    const char *key_sexp_s = "(public-key(dsa(p %m)(q %m)(g %m)(y %m)))";
    /* the signature */
    const char *sig_sexp_s = "(sig-val(dsa(r %m )(s %m )))";

    size_t erroff;
    gcry_mpi_t p, q, g, y, r, s, hash;
    p = q = g = y = r = s = hash = NULL;
    gcry_sexp_t key_sexp, hash_sexp, sig_sexp;
    key_sexp = hash_sexp = sig_sexp = NULL;

    int i_p_len = mpi_len( p_key->sig.dsa.p );
    int i_q_len = mpi_len( p_key->sig.dsa.q );
    int i_g_len = mpi_len( p_key->sig.dsa.g );
    int i_y_len = mpi_len( p_key->sig.dsa.y );
    if( gcry_mpi_scan( &p, GCRYMPI_FMT_USG, p_key->sig.dsa.p + 2, i_p_len, NULL ) ||
        gcry_mpi_scan( &q, GCRYMPI_FMT_USG, p_key->sig.dsa.q + 2, i_q_len, NULL ) ||
        gcry_mpi_scan( &g, GCRYMPI_FMT_USG, p_key->sig.dsa.g + 2, i_g_len, NULL ) ||
        gcry_mpi_scan( &y, GCRYMPI_FMT_USG, p_key->sig.dsa.y + 2, i_y_len, NULL ) ||
        gcry_sexp_build( &key_sexp, &erroff, key_sexp_s, p, q, g, y ) )
        goto out;

    uint8_t *p_r = sign->algo_specific.dsa.r;
    uint8_t *p_s = sign->algo_specific.dsa.s;
    int i_r_len = mpi_len( p_r );
    int i_s_len = mpi_len( p_s );
    if( gcry_mpi_scan( &r, GCRYMPI_FMT_USG, p_r + 2, i_r_len, NULL ) ||
        gcry_mpi_scan( &s, GCRYMPI_FMT_USG, p_s + 2, i_s_len, NULL ) ||
        gcry_sexp_build( &sig_sexp, &erroff, sig_sexp_s, r, s ) )
        goto out;

    int i_hash_len = gcry_md_get_algo_dlen (sign->digest_algo);
    if (i_hash_len > i_q_len)
        i_hash_len = i_q_len;
    if( gcry_mpi_scan( &hash, GCRYMPI_FMT_USG, p_hash, i_hash_len, NULL ) ||
        gcry_sexp_build( &hash_sexp, &erroff, hash_sexp_s, hash ) )
        goto out;

    if( gcry_pk_verify( sig_sexp, hash_sexp, key_sexp ) )
        goto out;

    ret = VLC_SUCCESS;

out:
    if( p ) gcry_mpi_release( p );
    if( q ) gcry_mpi_release( q );
    if( g ) gcry_mpi_release( g );
    if( y ) gcry_mpi_release( y );
    if( r ) gcry_mpi_release( r );
    if( s ) gcry_mpi_release( s );
    if( hash ) gcry_mpi_release( hash );
    if( key_sexp ) gcry_sexp_release( key_sexp );
    if( sig_sexp ) gcry_sexp_release( sig_sexp );
    if( hash_sexp ) gcry_sexp_release( hash_sexp );

    return ret;
}