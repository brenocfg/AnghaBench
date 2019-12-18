#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int b_vps; int b_sps; int b_pps; } ;
typedef  TYPE_1__ hevc_probe_ctx_t ;

/* Variables and functions */
 size_t H26X_MIN_PEEK ; 
 int const HEVC_NAL_AUD ; 
 int const HEVC_NAL_BLA_W_LP ; 
 int const HEVC_NAL_CRA ; 
 int const HEVC_NAL_PPS ; 
 int const HEVC_NAL_PREF_SEI ; 
 int const HEVC_NAL_SPS ; 
 int const HEVC_NAL_VPS ; 
 int hevc_getNALLayer (int const*) ; 
 int hevc_getNALType (int const*) ; 

__attribute__((used)) static int ProbeHEVC( const uint8_t *p_peek, size_t i_peek, void *p_priv )
{
    hevc_probe_ctx_t *p_ctx = (hevc_probe_ctx_t *) p_priv;

    if( i_peek < 2 )
        return -1;

    if( p_peek[0] & 0x80 )
        return -1;

    const uint8_t i_type = hevc_getNALType( p_peek );
    const uint8_t i_layer = hevc_getNALLayer( p_peek );

   if ( i_type == HEVC_NAL_VPS ) /* VPS */
   {
       if( i_layer != 0 || i_peek < 6 ||
           p_peek[4] != 0xFF || p_peek[5] != 0xFF ) /* Check reserved bits */
           return -1;
       p_ctx->b_vps = true;
       return 0;
   }
   else if( i_type == HEVC_NAL_SPS )  /* SPS */
   {
       if( i_layer != 0 )
           return -1;
       p_ctx->b_sps = true;
       return 0;
   }
   else if( i_type == HEVC_NAL_PPS )  /* PPS */
   {
       if( i_layer != 0 )
           return -1;
       p_ctx->b_pps = true;
       return 0;
   }
   else if( i_type >= HEVC_NAL_BLA_W_LP && i_type <= HEVC_NAL_CRA ) /* Key Frame */
   {
        if( p_ctx->b_vps && p_ctx->b_sps && p_ctx->b_pps && i_layer == 0 )
            return 1;
   }
   else if( i_type == HEVC_NAL_AUD ) /* AU */
   {
        if( i_peek < H26X_MIN_PEEK ||
            p_peek[4] != 0 || p_peek[5] != 0 ) /* Must prefix another NAL */
            return -1;
   }
   else if( i_type == HEVC_NAL_PREF_SEI ) /* Prefix SEI */
   {
       if( p_peek[2] == 0xFF ) /* empty SEI */
           return -1;
   }
   else
   {
       return -1; /* See 7.4.2.4.4 for sequence order */
   }

    return 0; /* Probe more */
}