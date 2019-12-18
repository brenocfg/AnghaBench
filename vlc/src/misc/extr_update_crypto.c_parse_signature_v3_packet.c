#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int hashed_data_len; int /*<<< orphan*/  timestamp; } ;
struct TYPE_6__ {TYPE_1__ v3; } ;
struct TYPE_7__ {int /*<<< orphan*/ * hash_verification; int /*<<< orphan*/  digest_algo; int /*<<< orphan*/  public_key_algo; int /*<<< orphan*/  issuer_longid; TYPE_2__ specific; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ signature_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static size_t parse_signature_v3_packet( signature_packet_t *p_sig,
                                      const uint8_t *p_buf, size_t i_sig_len )
{
    size_t i_read = 1; /* we already read the version byte */

    if( i_sig_len < 19 ) /* signature is at least 19 bytes + the 2 MPIs */
        return 0;

    p_sig->specific.v3.hashed_data_len = *p_buf++; i_read++;
    if( p_sig->specific.v3.hashed_data_len != 5 )
        return 0;

    p_sig->type = *p_buf++; i_read++;

    memcpy( p_sig->specific.v3.timestamp, p_buf, 4 );
    p_buf += 4; i_read += 4;

    memcpy( p_sig->issuer_longid, p_buf, 8 );
    p_buf += 8; i_read += 8;

    p_sig->public_key_algo = *p_buf++; i_read++;

    p_sig->digest_algo = *p_buf++; i_read++;

    p_sig->hash_verification[0] = *p_buf++; i_read++;
    p_sig->hash_verification[1] = *p_buf++; i_read++;

    assert( i_read == 19 );

    return i_read;
}