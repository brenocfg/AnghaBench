#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  g; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
struct TYPE_8__ {TYPE_2__ rsa; TYPE_1__ dsa; } ;
struct TYPE_9__ {int version; scalar_t__ algo; TYPE_3__ sig; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_4__ public_key_packet_t ;

/* Variables and functions */
 scalar_t__ GCRY_PK_DSA ; 
 scalar_t__ GCRY_PK_RSA ; 
 int /*<<< orphan*/  READ_MPI (int /*<<< orphan*/ ,int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int parse_public_key_packet( public_key_packet_t *p_key,
                                    const uint8_t *p_buf, size_t i_packet_len )
{
    if( i_packet_len < 6 )
        return VLC_EGENERIC;

    size_t i_read = 0;

    p_key->version   = *p_buf++; i_read++;
    if( p_key->version != 4 )
        return VLC_EGENERIC;

    /* XXX: warn when timestamp is > date ? */
    memcpy( p_key->timestamp, p_buf, 4 ); p_buf += 4; i_read += 4;

    p_key->algo      = *p_buf++; i_read++;
    if( p_key->algo == GCRY_PK_DSA ) {
        READ_MPI(p_key->sig.dsa.p, 3072);
        READ_MPI(p_key->sig.dsa.q, 256);
        READ_MPI(p_key->sig.dsa.g, 3072);
        READ_MPI(p_key->sig.dsa.y, 3072);
    } else if ( p_key->algo == GCRY_PK_RSA ) {
        READ_MPI(p_key->sig.rsa.n, 4096);
        READ_MPI(p_key->sig.rsa.e, 4096);
    } else
        return VLC_EGENERIC;

    if( i_read == i_packet_len )
        return VLC_SUCCESS;

    /* some extra data eh ? */

error:
    return VLC_EGENERIC;
}