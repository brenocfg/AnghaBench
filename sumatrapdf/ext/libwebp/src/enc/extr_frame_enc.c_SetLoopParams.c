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
typedef  int /*<<< orphan*/  VP8Encoder ;

/* Variables and functions */
 float Clamp (float,float,float) ; 
 int /*<<< orphan*/  ResetSSE (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ResetStats (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  SetSegmentProbas (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8SetSegmentParams (int /*<<< orphan*/ * const,float) ; 

__attribute__((used)) static void SetLoopParams(VP8Encoder* const enc, float q) {
  // Make sure the quality parameter is inside valid bounds
  q = Clamp(q, 0.f, 100.f);

  VP8SetSegmentParams(enc, q);      // setup segment quantizations and filters
  SetSegmentProbas(enc);            // compute segment probabilities

  ResetStats(enc);
  ResetSSE(enc);
}