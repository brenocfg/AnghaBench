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
typedef  int /*<<< orphan*/  WebPDecBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int WritePPMPAM (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int) ; 

int WebPWritePAM(FILE* fout, const WebPDecBuffer* const buffer) {
  return WritePPMPAM(fout, buffer, 1);
}