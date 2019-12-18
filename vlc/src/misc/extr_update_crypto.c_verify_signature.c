#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ public_key_algo; } ;
typedef  TYPE_1__ signature_packet_t ;
typedef  int /*<<< orphan*/  public_key_packet_t ;

/* Variables and functions */
 scalar_t__ GCRY_PK_DSA ; 
 scalar_t__ GCRY_PK_RSA ; 
 int VLC_EGENERIC ; 
 int verify_signature_dsa (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int verify_signature_rsa (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int verify_signature( signature_packet_t *sign, public_key_packet_t *p_key,
                      uint8_t *p_hash )
{
    if (sign->public_key_algo == GCRY_PK_DSA)
        return verify_signature_dsa(sign, p_key, p_hash);
    else if (sign->public_key_algo == GCRY_PK_RSA)
        return verify_signature_rsa(sign, p_key, p_hash);
    else
        return VLC_EGENERIC;
}