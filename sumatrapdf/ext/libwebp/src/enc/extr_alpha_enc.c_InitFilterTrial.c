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
struct TYPE_3__ {size_t score; int /*<<< orphan*/  bw; } ;
typedef  TYPE_1__ FilterTrial ;

/* Variables and functions */
 int /*<<< orphan*/  VP8BitWriterInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void InitFilterTrial(FilterTrial* const score) {
  score->score = (size_t)~0U;
  VP8BitWriterInit(&score->bw, 0);
}