#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int alert_message_time_remaining; int event_duration; int alert_priority; void* psz_alert_text; int /*<<< orphan*/  event_start_time; void* psz_nature_of_activation; scalar_t__* psz_eas_event_code; scalar_t__* rgc_eas_originator_code; void* i_eas_event_id; } ;
typedef  TYPE_1__ scte18_cea_t ;
struct TYPE_8__ {int* p_buffer; size_t i_buffer; } ;
typedef  TYPE_2__ block_t ;
typedef  int /*<<< orphan*/  atsc_a65_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_ADVANCE (int) ; 
#define  EAS_PRIORITY_HIGH 132 
#define  EAS_PRIORITY_LOW 131 
#define  EAS_PRIORITY_MAX 130 
#define  EAS_PRIORITY_MEDIUM 129 
#define  EAS_PRIORITY_TEST 128 
 int /*<<< orphan*/  GetDWBE (int const*) ; 
 void* GetWBE (int const*) ; 
 void* atsc_a65_Decode_multiple_string (int /*<<< orphan*/ *,int const*,size_t) ; 
 scalar_t__* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int const*,size_t) ; 
 int /*<<< orphan*/  scte18_cea_Free (TYPE_1__*) ; 
 TYPE_1__* scte18_cea_New () ; 

__attribute__((used)) static scte18_cea_t * scte18_cea_Decode( atsc_a65_handle_t *p_handle, const block_t *p_block )
{
    size_t len;
    scte18_cea_t *p_cea = scte18_cea_New();
    if( !p_cea )
        return NULL;

    const uint8_t *p_buffer = p_block->p_buffer;
    size_t i_buffer = p_block->i_buffer;

    if( i_buffer < 34 || p_buffer[0] != 0 )
        goto error;

    BUF_ADVANCE(1);

    p_cea->i_eas_event_id = GetWBE( p_buffer );
    BUF_ADVANCE(2);

    memcpy( p_cea->rgc_eas_originator_code, p_buffer, 3 );
    BUF_ADVANCE(3);

    len = p_buffer[0];
    if( i_buffer < 23 + len )
        goto error;
    p_cea->psz_eas_event_code = malloc( len + 1 );
    memcpy( p_cea->psz_eas_event_code, &p_buffer[1], len );
    p_cea->psz_eas_event_code[len] = 0;
    BUF_ADVANCE( len + 1 );

    len = p_buffer[0];
    if( i_buffer < len + 22 )
        goto error;
    p_cea->psz_nature_of_activation = atsc_a65_Decode_multiple_string( p_handle, &p_buffer[1], len );
    BUF_ADVANCE(1 + len);

    if( i_buffer < 21 )
        goto error;
    p_cea->alert_message_time_remaining = p_buffer[0];
    BUF_ADVANCE(1);

    p_cea->event_start_time = GetDWBE( p_buffer );
    BUF_ADVANCE(4);

    p_cea->event_duration = GetWBE( p_buffer );
    if( p_cea->event_duration != 0 && ( p_cea->event_duration < 15 || p_cea->event_duration > 6000 ) )
        goto error;
    BUF_ADVANCE(2);

    p_cea->alert_priority = p_buffer[1] & 0x0f;
    switch( p_cea->alert_priority )
    {
        case EAS_PRIORITY_TEST:
        case EAS_PRIORITY_LOW:
        case EAS_PRIORITY_MEDIUM:
        case EAS_PRIORITY_HIGH:
        case EAS_PRIORITY_MAX:
            break;
        default:
            goto error;
    }

    BUF_ADVANCE(2);

    BUF_ADVANCE(2); //OOB_ID

    BUF_ADVANCE(2); //
    BUF_ADVANCE(2); //

    BUF_ADVANCE(2); //audio_OOB_ID

    len = GetWBE( p_buffer );
    if( i_buffer < len + 2 )
        goto error;
    p_cea->psz_alert_text = atsc_a65_Decode_multiple_string( p_handle, &p_buffer[2], len );

    return p_cea;

error:
    scte18_cea_Free( p_cea );
    return NULL;
}