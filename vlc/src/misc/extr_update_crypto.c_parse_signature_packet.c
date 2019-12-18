#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/ * unhashed_data; int /*<<< orphan*/ * hashed_data; } ;
struct TYPE_14__ {TYPE_4__ v4; } ;
struct TYPE_11__ {int /*<<< orphan*/  s; } ;
struct TYPE_10__ {int /*<<< orphan*/  s; int /*<<< orphan*/  r; } ;
struct TYPE_12__ {TYPE_2__ rsa; TYPE_1__ dsa; } ;
struct TYPE_15__ {int version; scalar_t__ public_key_algo; int type; TYPE_5__ specific; TYPE_3__ algo_specific; } ;
typedef  TYPE_6__ signature_packet_t ;

/* Variables and functions */
#define  BINARY_SIGNATURE 133 
#define  CASUAL_KEY_SIGNATURE 132 
 scalar_t__ GCRY_PK_DSA ; 
 scalar_t__ GCRY_PK_RSA ; 
#define  GENERIC_KEY_SIGNATURE 131 
#define  PERSONA_KEY_SIGNATURE 130 
#define  POSITIVE_KEY_SIGNATURE 129 
 int /*<<< orphan*/  READ_MPI (int /*<<< orphan*/ ,int) ; 
#define  TEXT_SIGNATURE 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 size_t parse_signature_v3_packet (TYPE_6__*,int /*<<< orphan*/  const*,size_t) ; 
 size_t parse_signature_v4_packet (TYPE_6__*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int parse_signature_packet( signature_packet_t *p_sig,
                                   const uint8_t *p_buf, size_t i_packet_len )
{
    if( !i_packet_len ) /* 1st sanity check, we need at least the version */
        return VLC_EGENERIC;

    p_sig->version = *p_buf++;

    size_t i_read;
    switch( p_sig->version )
    {
        case 3:
            i_read = parse_signature_v3_packet( p_sig, p_buf, i_packet_len );
            break;
        case 4:
            p_sig->specific.v4.hashed_data = NULL;
            p_sig->specific.v4.unhashed_data = NULL;
            i_read = parse_signature_v4_packet( p_sig, p_buf, i_packet_len );
            break;
        default:
            return VLC_EGENERIC;
    }

    if( i_read == 0 ) /* signature packet parsing has failed */
        goto error;

    if( p_sig->public_key_algo != GCRY_PK_DSA && p_sig->public_key_algo != GCRY_PK_RSA )
        goto error;

    switch( p_sig->type )
    {
        case BINARY_SIGNATURE:
        case TEXT_SIGNATURE:
        case GENERIC_KEY_SIGNATURE:
        case PERSONA_KEY_SIGNATURE:
        case CASUAL_KEY_SIGNATURE:
        case POSITIVE_KEY_SIGNATURE:
            break;
        default:
            goto error;
    }

    p_buf--; /* rewind to the version byte */
    p_buf += i_read;

    if( p_sig->public_key_algo == GCRY_PK_DSA ) {
        READ_MPI(p_sig->algo_specific.dsa.r, 256);
        READ_MPI(p_sig->algo_specific.dsa.s, 256);
    } else if ( p_sig->public_key_algo == GCRY_PK_RSA ) {
        READ_MPI(p_sig->algo_specific.rsa.s, 4096);
    } else
        goto error;

    assert( i_read == i_packet_len );
    if( i_read < i_packet_len ) /* some extra data, hm ? */
        goto error;

    return VLC_SUCCESS;

error:

    if( p_sig->version == 4 )
    {
        free( p_sig->specific.v4.hashed_data );
        free( p_sig->specific.v4.unhashed_data );
    }

    return VLC_EGENERIC;
}