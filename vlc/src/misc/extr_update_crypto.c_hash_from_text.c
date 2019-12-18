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
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  digest_algo; } ;
typedef  TYPE_1__ signature_packet_t ;
typedef  int /*<<< orphan*/  gcry_md_hd_t ;

/* Variables and functions */
 scalar_t__ TEXT_SIGNATURE ; 
 scalar_t__ gcry_md_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_putc (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  gcry_md_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/ * hash_finish (int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t strcspn (char const*,char*) ; 
 size_t strlen (char const*) ; 

uint8_t *hash_from_text( const char *psz_string,
        signature_packet_t *p_sig )
{
    gcry_md_hd_t hd;
    if( gcry_md_open( &hd, p_sig->digest_algo, 0 ) )
        return NULL;

    if( p_sig->type == TEXT_SIGNATURE )
    while( *psz_string )
    {
        size_t i_len = strcspn( psz_string, "\r\n" );

        if( i_len )
        {
            gcry_md_write( hd, psz_string, i_len );
            psz_string += i_len;
        }
        gcry_md_putc( hd, '\r' );
        gcry_md_putc( hd, '\n' );

        if( *psz_string == '\r' )
            psz_string++;
        if( *psz_string == '\n' )
            psz_string++;
    }
    else
        gcry_md_write( hd, psz_string, strlen( psz_string ) );

    return hash_finish( hd, p_sig );
}