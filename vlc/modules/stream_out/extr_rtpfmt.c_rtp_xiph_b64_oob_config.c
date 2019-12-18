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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetDWBE (int*,int) ; 
 int /*<<< orphan*/  SetWBE (int*,size_t) ; 
 scalar_t__ VLC_SUCCESS ; 
 int XIPH_IDENT ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ rtp_xiph_pack_headers (int,void*,size_t,int**,size_t*,int*) ; 
 char* vlc_b64_encode_binary (int*,size_t) ; 

__attribute__((used)) static char *rtp_xiph_b64_oob_config(void *p_extra, size_t i_extra,
                                     uint8_t *theora_pixel_fmt)
{
    uint8_t *p_buffer;
    size_t i_buffer;
    if (rtp_xiph_pack_headers(9, p_extra, i_extra, &p_buffer, &i_buffer,
                              theora_pixel_fmt) != VLC_SUCCESS)
        return NULL;

    /* Number of packed headers */
    SetDWBE(p_buffer, 1);
    /* Ident */
    uint32_t ident = XIPH_IDENT;
    SetWBE(p_buffer + 4, ident >> 8);
    p_buffer[6] = ident & 0xff;
    /* Length field */
    SetWBE(p_buffer + 7, i_buffer);

    char *config = vlc_b64_encode_binary(p_buffer, i_buffer);
    free(p_buffer);
    return config;
}