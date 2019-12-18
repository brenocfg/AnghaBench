#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  enum cc_payload_type_e { ____Placeholder_cc_payload_type_e } cc_payload_type_e ;
typedef  int /*<<< orphan*/  cc_data_t ;

/* Variables and functions */
 int CC_PAYLOAD_DVD ; 
 int CC_PAYLOAD_GA94 ; 
 int CC_PAYLOAD_REPLAYTV ; 
 int CC_PAYLOAD_SCTE20 ; 
 int V (int const) ; 
 int /*<<< orphan*/  cc_Extract (int /*<<< orphan*/ *,int,int,int const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcmp (int const*,int const*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static inline void cc_ProbeAndExtract( cc_data_t *c, bool b_top_field_first, const uint8_t *p_src, int i_src )
{
    static const uint8_t p_cc_ga94[4] = { 0x47, 0x41, 0x39, 0x34 };
    static const uint8_t p_cc_dvd[4] = { 0x43, 0x43, 0x01, 0xf8 }; /* ascii 'CC', type_code, cc_block_size */
    static const uint8_t p_cc_replaytv4a[2] = { 0xbb, 0x02 };/* RTV4K, BB02xxxxCC02 */
    static const uint8_t p_cc_replaytv4b[2] = { 0xcc, 0x02 };/* see DVR-ClosedCaption in samples */
    static const uint8_t p_cc_replaytv5a[2] = { 0x99, 0x02 };/* RTV5K, 9902xxxxAA02 */
    static const uint8_t p_cc_replaytv5b[2] = { 0xaa, 0x02 };/* see DVR-ClosedCaption in samples */
    static const uint8_t p_cc_scte20[2] = { 0x03, 0x81 };    /* user_data_type_code, SCTE 20 */
    static const uint8_t p_cc_scte20_old[2] = { 0x03, 0x01 };/* user_data_type_code, old, Note 1 */

    if( i_src < 4 )
        return;

    enum cc_payload_type_e i_payload_type;
    if( !memcmp( p_cc_ga94, p_src, 4 ) && i_src >= 5+1+1+1 && p_src[4] == 0x03 )
    {
        /* CC from DVB/ATSC TS */
        i_payload_type = CC_PAYLOAD_GA94;
        i_src -= 5;
        p_src += 5;
    }
    else if( !memcmp( p_cc_dvd, p_src, 4 ) && i_src > 4+1 )
    {
        i_payload_type = CC_PAYLOAD_DVD;
    }
    else if( i_src >= 2+2 + 2+2 &&
             ( ( !memcmp( p_cc_replaytv4a, &p_src[0], 2 ) && !memcmp( p_cc_replaytv4b, &p_src[4], 2 ) ) ||
               ( !memcmp( p_cc_replaytv5a, &p_src[0], 2 ) && !memcmp( p_cc_replaytv5b, &p_src[4], 2 ) ) ) )
    {
        i_payload_type = CC_PAYLOAD_REPLAYTV;
    }
    else if( ( !memcmp( p_cc_scte20, p_src, 2 ) ||
               !memcmp( p_cc_scte20_old, p_src, 2 ) ) && i_src > 2 )
    {
        i_payload_type = CC_PAYLOAD_SCTE20;
    }
    else if (p_src[0] == 0x03 && p_src[1] == i_src - 2) /* DIRECTV */
    {
        i_payload_type = CC_PAYLOAD_GA94;
        i_src -= 2;
        p_src += 2;
    }
    else
    {
#if 0
#define V(x) ( ( x < 0x20 || x >= 0x7f ) ? '?' : x )
        fprintf( stderr, "-------------- unknown user data " );
        for( int i = 0; i < i_src; i++ )
            fprintf( stderr, "%2.2x ", p_src[i] );
        for( int i = 0; i < i_src; i++ )
            fprintf( stderr, "%c ", V(p_src[i]) );
        fprintf( stderr, "\n" );
#undef V
#endif
        return;
    }

    cc_Extract( c, i_payload_type, b_top_field_first, p_src, i_src );
}