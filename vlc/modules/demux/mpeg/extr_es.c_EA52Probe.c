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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  EA52CheckSyncProbe ; 
 int /*<<< orphan*/  GenericFormatCheck ; 
 int GenericProbe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_A52_MIN_HEADER_SIZE ; 
 int /*<<< orphan*/  const WAVE_FORMAT_A52 ; 
 int /*<<< orphan*/  const WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  const WAVE_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  WAV_EXTRA_PROBE_SIZE ; 

__attribute__((used)) static int EA52Probe( demux_t *p_demux, uint64_t *pi_offset )
{
    const char *ppsz_name[] = { "eac3", NULL };
    const uint16_t rgi_twocc[] = { WAVE_FORMAT_PCM, WAVE_FORMAT_A52, WAVE_FORMAT_UNKNOWN };

    return GenericProbe( p_demux, pi_offset, ppsz_name, EA52CheckSyncProbe,
                         VLC_A52_MIN_HEADER_SIZE,
                         1920 + VLC_A52_MIN_HEADER_SIZE + 1,
                         WAV_EXTRA_PROBE_SIZE,
                         true, rgi_twocc, GenericFormatCheck );
}