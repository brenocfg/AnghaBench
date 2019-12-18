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
typedef  void vlc_keystore ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CryptProtectData ; 
 size_t Process (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 

__attribute__((used)) static size_t Encrypt( vlc_keystore *p_keystore, void *p_ctx, const uint8_t *p_src,
                       size_t i_src_len, uint8_t ** pp_dst )
{
    VLC_UNUSED( p_keystore );
    VLC_UNUSED( p_ctx );
    return Process( p_src, i_src_len, pp_dst, CryptProtectData );
}