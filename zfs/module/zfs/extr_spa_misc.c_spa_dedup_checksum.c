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
struct TYPE_3__ {int spa_dedup_checksum; } ;
typedef  TYPE_1__ spa_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;

/* Variables and functions */

enum zio_checksum
spa_dedup_checksum(spa_t *spa)
{
	return (spa->spa_dedup_checksum);
}