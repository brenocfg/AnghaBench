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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int CompareValues(uint32_t a, uint32_t b, const char* output_str) {
  if (a != b) {
    fprintf(stderr, "%s: %d vs %d\n", output_str, a, b);
    return 0;
  }
  return 1;
}