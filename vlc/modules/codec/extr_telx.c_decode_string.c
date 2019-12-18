#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int** pi_active_national_set; } ;
typedef  TYPE_1__ decoder_sys_t ;

/* Variables and functions */
 int bytereverse (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  to_utf8 (char*,int) ; 

__attribute__((used)) static void decode_string( char * res, int res_len,
                           decoder_sys_t *p_sys, int magazine,
                           const uint8_t * packet, int len )
{
    char utf8[7];
    char * pt = res;

    for ( int i = 0; i < len; i++ )
    {
        int in = bytereverse( packet[i] ) & 0x7f;
        uint16_t out = 32;
        size_t l;

        switch ( in )
        {
        /* special national characters */
        case 0x23:
            out = p_sys->pi_active_national_set[magazine][0];
            break;
        case 0x24:
            out = p_sys->pi_active_national_set[magazine][1];
            break;
        case 0x40:
            out = p_sys->pi_active_national_set[magazine][2];
            break;
        case 0x5b:
            out = p_sys->pi_active_national_set[magazine][3];
            break;
        case 0x5c:
            out = p_sys->pi_active_national_set[magazine][4];
            break;
        case 0x5d:
            out = p_sys->pi_active_national_set[magazine][5];
            break;
        case 0x5e:
            out = p_sys->pi_active_national_set[magazine][6];
            break;
        case 0x5f:
            out = p_sys->pi_active_national_set[magazine][7];
            break;
        case 0x60:
            out = p_sys->pi_active_national_set[magazine][8];
            break;
        case 0x7b:
            out = p_sys->pi_active_national_set[magazine][9];
            break;
        case 0x7c:
            out = p_sys->pi_active_national_set[magazine][10];
            break;
        case 0x7d:
            out = p_sys->pi_active_national_set[magazine][11];
            break;
        case 0x7e:
            out = p_sys->pi_active_national_set[magazine][12];
            break;

        /* some special control characters (empirical) */
        case 0x0d:
            /* apparently this starts a sequence that ends with 0xb 0xb */
            while ( i + 1 < len && (bytereverse( packet[i+1] ) & 0x7f) != 0x0b )
                i++;
            i += 2;
            break;
            /* goto skip; */

        default:
            /* non documented national range 0x08 - 0x0f */
            if ( in >= 0x08 && in <= 0x0f )
            {
                out = p_sys->pi_active_national_set[magazine][13 + in - 8];
                break;
            }

            /* normal ascii */
            if ( in > 32 && in < 0x7f )
                out = in;
        }

        /* handle undefined national characters */
        if ( out == 0 )
            out = 32;

        /* convert to utf-8 */
        to_utf8( utf8, out );
        l = strlen( utf8 );
        if ( pt + l < res + res_len - 1 )
        {
            strcpy(pt, utf8);
            pt += l;
        }

        /* skip: ; */
    }
    /* end: */
    *pt++ = 0;
}