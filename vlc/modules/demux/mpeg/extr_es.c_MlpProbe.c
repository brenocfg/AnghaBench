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
 int /*<<< orphan*/  BASE_PROBE_SIZE ; 
 int /*<<< orphan*/  GenericFormatCheck ; 
 int GenericProbe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MlpCheckSync ; 
 int /*<<< orphan*/  const WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  const WAVE_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  WAV_EXTRA_PROBE_SIZE ; 

__attribute__((used)) static int MlpProbe( demux_t *p_demux, uint64_t *pi_offset )
{
    const char *ppsz_name[] = { "mlp", NULL };
    const uint16_t rgi_twocc[] = { WAVE_FORMAT_PCM, WAVE_FORMAT_UNKNOWN };

    return GenericProbe( p_demux, pi_offset, ppsz_name, MlpCheckSync,
                         4+28+16*4, BASE_PROBE_SIZE, WAV_EXTRA_PROBE_SIZE,
                         false, rgi_twocc, GenericFormatCheck );
}