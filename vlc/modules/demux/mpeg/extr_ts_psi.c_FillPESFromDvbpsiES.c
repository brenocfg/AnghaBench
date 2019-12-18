#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_65__   TYPE_9__ ;
typedef  struct TYPE_64__   TYPE_6__ ;
typedef  struct TYPE_63__   TYPE_5__ ;
typedef  struct TYPE_62__   TYPE_4__ ;
typedef  struct TYPE_61__   TYPE_3__ ;
typedef  struct TYPE_60__   TYPE_2__ ;
typedef  struct TYPE_59__   TYPE_1__ ;

/* Type definitions */
typedef  void* ts_transport_type_t ;
struct TYPE_60__ {int i_stream_type; TYPE_9__* p_es; void* transport; } ;
typedef  TYPE_2__ ts_stream_t ;
typedef  int /*<<< orphan*/  ts_pmt_t ;
typedef  scalar_t__ ts_pmt_registration_type_t ;
struct TYPE_61__ {int /*<<< orphan*/  i_program_number; } ;
typedef  TYPE_3__ dvbpsi_pmt_t ;
struct TYPE_62__ {int i_type; int i_pid; } ;
typedef  TYPE_4__ dvbpsi_pmt_es_t ;
struct TYPE_63__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_64__ {scalar_t__ b_es_id_pid; } ;
typedef  TYPE_6__ demux_sys_t ;
struct TYPE_59__ {scalar_t__ i_cat; int b_packetized; int i_id; int /*<<< orphan*/  i_group; void* i_priority; } ;
struct TYPE_65__ {TYPE_1__ fmt; } ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 void* ES_PRIORITY_NOT_DEFAULTABLE ; 
 void* ES_PRIORITY_SELECTABLE_MIN ; 
 int /*<<< orphan*/  PIDFillFormat (TYPE_5__*,TYPE_2__*,int,void**) ; 
 scalar_t__ PMTEsHasRegistration (TYPE_5__*,TYPE_4__ const*,char*) ; 
 int /*<<< orphan*/  PMTSetupEs0x02 (TYPE_9__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  PMTSetupEs0x05PrivateData (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  PMTSetupEs0x06 (TYPE_5__*,TYPE_2__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  PMTSetupEs0x83 (TYPE_3__ const*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  PMTSetupEs0xA0 (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  PMTSetupEs0xD1 (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  PMTSetupEs0xEA (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int PMTSetupEsHDMV (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int PMTSetupEsRegistration (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  SetupAVCDescriptors (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  SetupAudioExtendedDescriptors (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  SetupISO14496Descriptors (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/  const*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  SetupJ2KDescriptors (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  SetupMetadataDescriptors (TYPE_5__*,TYPE_2__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  SetupStandardESDescriptors (TYPE_5__*,TYPE_9__*,TYPE_4__ const*) ; 
 scalar_t__ TS_PMT_REGISTRATION_BLURAY ; 
 void* TS_TRANSPORT_IGNORE ; 
 void* TS_TRANSPORT_PES ; 
 void* TS_TRANSPORT_SECTIONS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,int,int) ; 

__attribute__((used)) static void FillPESFromDvbpsiES( demux_t *p_demux,
                                 const dvbpsi_pmt_t *p_dvbpsipmt,
                                 const dvbpsi_pmt_es_t *p_dvbpsies,
                                 ts_pmt_registration_type_t registration_type,
                                 const ts_pmt_t *p_pmt,
                                 ts_stream_t *p_pes )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    ts_transport_type_t type_change = TS_TRANSPORT_PES;
    PIDFillFormat( p_demux, p_pes, p_dvbpsies->i_type, &type_change );

    p_pes->i_stream_type = p_dvbpsies->i_type;

    bool b_registration_applied = false;
    if ( p_dvbpsies->i_type >= 0x80 ) /* non standard, extensions */
    {
        if ( registration_type == TS_PMT_REGISTRATION_BLURAY )
        {
            if (( b_registration_applied = PMTSetupEsHDMV( p_demux, p_pes->p_es, p_dvbpsies ) ))
                msg_Dbg( p_demux, "    + HDMV registration applied to pid %d type 0x%x",
                         p_dvbpsies->i_pid, p_dvbpsies->i_type );
        }
        else
        {
            if (( b_registration_applied = PMTSetupEsRegistration( p_demux, p_pes->p_es, p_dvbpsies ) ))
                msg_Dbg( p_demux, "    + registration applied to pid %d type 0x%x",
                    p_dvbpsies->i_pid, p_dvbpsies->i_type );
        }
    }

    if ( !b_registration_applied )
    {
        p_pes->transport = type_change; /* Only change type if registration has not changed meaning */

        switch( p_dvbpsies->i_type )
        {
        case 0x02:
            PMTSetupEs0x02( p_pes->p_es, p_dvbpsies );
            break;
        case 0x05: /* Private data in sections */
            p_pes->transport = TS_TRANSPORT_SECTIONS;
            PMTSetupEs0x05PrivateData( p_demux, p_pes->p_es, p_dvbpsies );
            break;
        case 0x06:
            /* Handle PES private data */
            PMTSetupEs0x06( p_demux, p_pes, p_dvbpsies );
            break;
        case 0x0a: /* DSM-CC */
        case 0x0b:
        case 0x0c:
        case 0x0d:
            p_pes->transport = TS_TRANSPORT_IGNORE;
            break;
        /* All other private or reserved types */
        case 0x13: /* SL in sections */
            p_pes->transport = TS_TRANSPORT_SECTIONS;
            /* fallthrough */
        case 0x0f:
        case 0x10:
        case 0x11:
        case 0x12:
            SetupISO14496Descriptors( p_demux, p_pes, p_pmt, p_dvbpsies );
            break;
        case 0x15:
            SetupMetadataDescriptors( p_demux, p_pes, p_dvbpsies );
            break;
        case 0x1b:
            SetupAVCDescriptors( p_demux, p_pes->p_es, p_dvbpsies );
            break;
        case 0x21:
            SetupJ2KDescriptors( p_demux, p_pes->p_es, p_dvbpsies );
            break;
        case 0x83:
            /* LPCM (audio) */
            PMTSetupEs0x83( p_dvbpsipmt, p_pes->p_es, p_dvbpsies->i_pid );
            break;
        case 0xa0:
            PMTSetupEs0xA0( p_demux, p_pes->p_es, p_dvbpsies );
            break;
        case 0xd1:
            PMTSetupEs0xD1( p_demux, p_pes->p_es, p_dvbpsies );
            break;
        case 0xEA:
            PMTSetupEs0xEA( p_demux, p_pes->p_es, p_dvbpsies );
        default:
            break;
        }
    }

    if( p_pes->p_es->fmt.i_cat == AUDIO_ES )
    {
        SetupAudioExtendedDescriptors( p_demux, p_pes->p_es, p_dvbpsies );
    }

    SetupStandardESDescriptors(  p_demux, p_pes->p_es, p_dvbpsies );

    if ( registration_type == TS_PMT_REGISTRATION_BLURAY )
    {
        /*
         * 0x1011 primary video
         * 0x1100- 0x111f primary audio
         * 0x1a00- 0x1a1f secondary audio
         * 0x1b00- 0x1b1f secondary video */

        /* Disable dolbyvision */
        if ( p_dvbpsies->i_pid == 0x1015 &&
            PMTEsHasRegistration( p_demux, p_dvbpsies, "HDMV" ) )
        {
            p_pes->p_es->fmt.i_priority = ES_PRIORITY_NOT_DEFAULTABLE;
        }
        else if( (p_dvbpsies->i_pid >= 0x1a00 && p_dvbpsies->i_pid <= 0x1a1f) ||
                 (p_dvbpsies->i_pid >= 0x1b00 && p_dvbpsies->i_pid <= 0x1b1f) )
        {
            /* We might just want to prio, but it will trigger multiple videos es */
            p_pes->p_es->fmt.i_priority = ES_PRIORITY_NOT_DEFAULTABLE;
        }
        else
        {
            p_pes->p_es->fmt.i_priority = 0xFFFF - (p_dvbpsies->i_pid & 0xFFFF) +
                                                    ES_PRIORITY_SELECTABLE_MIN;
        }
    }

    /* PES packets usually contain truncated frames */
    p_pes->p_es->fmt.b_packetized = false;

    /* Set Groups / ID */
    p_pes->p_es->fmt.i_group = p_dvbpsipmt->i_program_number;
    if( p_sys->b_es_id_pid )
        p_pes->p_es->fmt.i_id = p_dvbpsies->i_pid;
}