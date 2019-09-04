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
struct TYPE_3__ {int d; size_t k; scalar_t__ f; int splitPoint; } ;
typedef  TYPE_1__ ZDICT_fastCover_params_t ;

/* Variables and functions */
 scalar_t__ FASTCOVER_MAX_F ; 

__attribute__((used)) static int FASTCOVER_checkParameters(ZDICT_fastCover_params_t parameters,
                                 size_t maxDictSize) {
  /* k, d, and f are required parameters */
  if (parameters.d == 0 || parameters.k == 0 || parameters.f == 0) {
    return 0;
  }
  /* d has to be 6 or 8 */
  if (parameters.d != 6 && parameters.d != 8) {
    return 0;
  }
  /* 0 < f <= FASTCOVER_MAX_F */
  if (parameters.f > FASTCOVER_MAX_F) {
    return 0;
  }
  /* k <= maxDictSize */
  if (parameters.k > maxDictSize) {
    return 0;
  }
  /* d <= k */
  if (parameters.d > parameters.k) {
    return 0;
  }
  /* 0 < splitPoint <= 1 */
  if (parameters.splitPoint <= 0 || parameters.splitPoint > 1) {
    return 0;
  }
  return 1;
}