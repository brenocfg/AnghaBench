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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  hevc_video_parameter_set_t ;
typedef  int /*<<< orphan*/  hevc_sequence_parameter_set_t ;
typedef  int /*<<< orphan*/  hevc_picture_parameter_set_t ;
struct TYPE_3__ {int /*<<< orphan*/  rg_pps; int /*<<< orphan*/  rg_sps; int /*<<< orphan*/  rg_vps; } ;
typedef  TYPE_1__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPENDIF (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HEVC_PPS_ID_MAX ; 
 int /*<<< orphan*/  HEVC_SPS_ID_MAX ; 
 int /*<<< orphan*/  HEVC_VPS_ID_MAX ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SetsToAnnexB(decoder_sys_t *p_sys,
                         const hevc_picture_parameter_set_t *p_pps,
                         const hevc_sequence_parameter_set_t *p_sps,
                         const hevc_video_parameter_set_t *p_vps,
                         uint8_t **pp_out, int *pi_out)
{
    uint8_t *p_data = NULL;
    size_t i_data = 0;

    APPENDIF(HEVC_VPS_ID_MAX, p_vps, p_sys->rg_vps, true);
    APPENDIF(HEVC_VPS_ID_MAX, p_vps, p_sys->rg_vps, false);
    APPENDIF(HEVC_SPS_ID_MAX, p_sps, p_sys->rg_sps, true);
    APPENDIF(HEVC_SPS_ID_MAX, p_sps, p_sys->rg_sps, false);
    APPENDIF(HEVC_PPS_ID_MAX, p_pps, p_sys->rg_pps, true);
    APPENDIF(HEVC_PPS_ID_MAX, p_pps, p_sys->rg_pps, false);

    /* because we copy to i_extra :/ */
    if(i_data <= INT_MAX)
    {
        *pp_out = p_data;
        *pi_out = i_data;
    }
    else free(p_data);
}