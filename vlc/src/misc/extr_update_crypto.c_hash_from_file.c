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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  digest_algo; } ;
typedef  TYPE_1__ signature_packet_t ;
typedef  int /*<<< orphan*/  gcry_md_hd_t ;

/* Variables and functions */
 int /*<<< orphan*/  gcry_md_close (int /*<<< orphan*/ ) ; 
 scalar_t__ gcry_md_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_finish (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ hash_from_binary_file (char const*,int /*<<< orphan*/ ) ; 

uint8_t *hash_from_file( const char *psz_file, signature_packet_t *p_sig )
{
    gcry_md_hd_t hd;
    if( gcry_md_open( &hd, p_sig->digest_algo, 0 ) )
        return NULL;

    if( hash_from_binary_file( psz_file, hd ) < 0 )
    {
        gcry_md_close( hd );
        return NULL;
    }

    return hash_finish( hd, p_sig );
}