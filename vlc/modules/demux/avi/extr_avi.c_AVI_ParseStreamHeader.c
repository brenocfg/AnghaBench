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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int uint8_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int AUDIO_ES ; 
#define  AVITWOCC_AC 134 
#define  AVITWOCC_db 133 
#define  AVITWOCC_dc 132 
#define  AVITWOCC_pc 131 
#define  AVITWOCC_sb 130 
#define  AVITWOCC_tx 129 
#define  AVITWOCC_wb 128 
 int IGNORE_ES ; 
 int SPU_ES ; 
 int UNKNOWN_ES ; 
 int VIDEO_ES ; 
 int VLC_TWOCC (int,int) ; 

__attribute__((used)) static void AVI_ParseStreamHeader( vlc_fourcc_t i_id,
                                   unsigned int *pi_number,
                                   enum es_format_category_e *pi_type )
{
    int c1, c2;

    c1 = ((uint8_t *)&i_id)[0];
    c2 = ((uint8_t *)&i_id)[1];

    if( c1 < '0' || c1 > '9' || c2 < '0' || c2 > '9' )
    {
        *pi_number =  100; /* > max stream number */
        *pi_type = UNKNOWN_ES;
    }
    else
    {
        *pi_number = (c1 - '0') * 10 + (c2 - '0' );
        switch( VLC_TWOCC( ((uint8_t *)&i_id)[2], ((uint8_t *)&i_id)[3] ) )
        {
            case AVITWOCC_wb:
                *pi_type = AUDIO_ES;
                break;
            case AVITWOCC_dc:
            case AVITWOCC_db:
            case AVITWOCC_AC:
                *pi_type = VIDEO_ES;
                break;
            case AVITWOCC_tx:
            case AVITWOCC_sb:
                *pi_type = SPU_ES;
                break;
            case AVITWOCC_pc:
                *pi_type = IGNORE_ES;
                break;
            default:
                *pi_type = UNKNOWN_ES;
                break;
        }
    }
}