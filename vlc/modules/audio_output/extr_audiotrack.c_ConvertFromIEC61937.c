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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int i_buffer; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_1__ block_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int GetWBE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static int
ConvertFromIEC61937( audio_output_t *p_aout, block_t *p_buffer )
{
    /* This function is only used for Android API 23 when AudioTrack is
     * configured with ENCODING_ AC3/E_AC3/DTS. In that case, only the codec
     * data is needed (without the IEC61937 encapsulation). This function
     * recovers the codec data from an EC61937 frame. It is the opposite of the
     * code found in converter/tospdif.c. We could also request VLC core to
     * send us the codec data directly, but in that case, we wouldn't benefit
     * from the eac3 block merger of tospdif.c. */

    VLC_UNUSED( p_aout );
    uint8_t i_length_mul;

    if( p_buffer->i_buffer < 6 )
        return -1;

    switch( GetWBE( &p_buffer->p_buffer[4] ) & 0xFF )
    {
        case 0x01: /* IEC61937_AC3 */
            i_length_mul = 8;
            break;
        case 0x15: /* IEC61937_EAC3 */
            i_length_mul = 1;
            break;
        case 0x0B: /* IEC61937_DTS1 */
        case 0x0C: /* IEC61937_DTS2 */
        case 0x0D: /* IEC61937_DTS3 */
            i_length_mul = 8;
            break;
        case 0x11: /* IEC61937_DTSHD */
            i_length_mul = 1;
            break;
        default:
            vlc_assert_unreachable();
    }
    uint16_t i_length = GetWBE( &p_buffer->p_buffer[6] );
    if( i_length == 0 )
        return -1;

    i_length /= i_length_mul;
    if( i_length > p_buffer->i_buffer - 8 )
        return -1;

    p_buffer->p_buffer += 8; /* SPDIF_HEADER_SIZE */
    p_buffer->i_buffer = i_length;

    return 0;
}