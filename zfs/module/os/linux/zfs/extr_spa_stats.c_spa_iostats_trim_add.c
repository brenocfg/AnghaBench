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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ trim_type_t ;
struct TYPE_8__ {TYPE_4__* kstat; } ;
struct TYPE_6__ {TYPE_3__ iostats; } ;
struct TYPE_7__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  spa_iostats_t ;
typedef  TYPE_3__ spa_history_kstat_t ;
struct TYPE_9__ {int /*<<< orphan*/ * ks_data; } ;
typedef  TYPE_4__ kstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_IOSTATS_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRIM_TYPE_MANUAL ; 
 int /*<<< orphan*/  autotrim_bytes_failed ; 
 int /*<<< orphan*/  autotrim_bytes_skipped ; 
 int /*<<< orphan*/  autotrim_bytes_written ; 
 int /*<<< orphan*/  autotrim_extents_failed ; 
 int /*<<< orphan*/  autotrim_extents_skipped ; 
 int /*<<< orphan*/  autotrim_extents_written ; 
 int /*<<< orphan*/  trim_bytes_failed ; 
 int /*<<< orphan*/  trim_bytes_skipped ; 
 int /*<<< orphan*/  trim_bytes_written ; 
 int /*<<< orphan*/  trim_extents_failed ; 
 int /*<<< orphan*/  trim_extents_skipped ; 
 int /*<<< orphan*/  trim_extents_written ; 

void
spa_iostats_trim_add(spa_t *spa, trim_type_t type,
    uint64_t extents_written, uint64_t bytes_written,
    uint64_t extents_skipped, uint64_t bytes_skipped,
    uint64_t extents_failed, uint64_t bytes_failed)
{
	spa_history_kstat_t *shk = &spa->spa_stats.iostats;
	kstat_t *ksp = shk->kstat;
	spa_iostats_t *iostats;

	if (ksp == NULL)
		return;

	iostats = ksp->ks_data;
	if (type == TRIM_TYPE_MANUAL) {
		SPA_IOSTATS_ADD(trim_extents_written, extents_written);
		SPA_IOSTATS_ADD(trim_bytes_written, bytes_written);
		SPA_IOSTATS_ADD(trim_extents_skipped, extents_skipped);
		SPA_IOSTATS_ADD(trim_bytes_skipped, bytes_skipped);
		SPA_IOSTATS_ADD(trim_extents_failed, extents_failed);
		SPA_IOSTATS_ADD(trim_bytes_failed, bytes_failed);
	} else {
		SPA_IOSTATS_ADD(autotrim_extents_written, extents_written);
		SPA_IOSTATS_ADD(autotrim_bytes_written, bytes_written);
		SPA_IOSTATS_ADD(autotrim_extents_skipped, extents_skipped);
		SPA_IOSTATS_ADD(autotrim_bytes_skipped, bytes_skipped);
		SPA_IOSTATS_ADD(autotrim_extents_failed, extents_failed);
		SPA_IOSTATS_ADD(autotrim_bytes_failed, bytes_failed);
	}
}