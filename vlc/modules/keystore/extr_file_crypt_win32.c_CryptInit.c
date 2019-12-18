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
typedef  int /*<<< orphan*/  vlc_keystore ;
struct crypt {int /*<<< orphan*/  pf_encrypt; int /*<<< orphan*/  pf_decrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  Decrypt ; 
 int /*<<< orphan*/  Encrypt ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 

int CryptInit(vlc_keystore *p_keystore, struct crypt *p_crypt)
{
    VLC_UNUSED( p_keystore );
    p_crypt->pf_decrypt = Decrypt;
    p_crypt->pf_encrypt = Encrypt;
    return VLC_SUCCESS;
}