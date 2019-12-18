#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_decoder; } ;
typedef  TYPE_1__ dvbpsi_t ;
typedef  int /*<<< orphan*/  dvbpsi_psi_section_t ;

/* Variables and functions */
 int /*<<< orphan*/  ts_dvbpsi_RawSubDecoderGatherSections (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ts_dvbpsi_RawDecoderGatherSections( dvbpsi_t *p_dvbpsi,
                                                dvbpsi_psi_section_t * p_section )
{
    ts_dvbpsi_RawSubDecoderGatherSections( p_dvbpsi, p_dvbpsi->p_decoder, p_section );
}