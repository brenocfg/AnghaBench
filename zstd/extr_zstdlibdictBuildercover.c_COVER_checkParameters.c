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
struct TYPE_3__ {size_t d; size_t k; int splitPoint; } ;
typedef  TYPE_1__ ZDICT_cover_params_t ;

/* Variables and functions */

__attribute__((used)) static int COVER_checkParameters(ZDICT_cover_params_t parameters,
                                 size_t maxDictSize) {
  /* k and d are required parameters */
  if (parameters.d == 0 || parameters.k == 0) {
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
  if (parameters.splitPoint <= 0 || parameters.splitPoint > 1){
    return 0;
  }
  return 1;
}