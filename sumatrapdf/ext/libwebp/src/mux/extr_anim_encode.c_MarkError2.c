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
struct TYPE_3__ {int /*<<< orphan*/  error_str_; } ;
typedef  TYPE_1__ WebPAnimEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_STR_MAX_LENGTH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 

__attribute__((used)) static void MarkError2(WebPAnimEncoder* const enc,
                       const char* str, int error_code) {
  if (snprintf(enc->error_str_, ERROR_STR_MAX_LENGTH, "%s: %d.", str,
               error_code) < 0) {
    assert(0);  // FIX ME!
  }
}