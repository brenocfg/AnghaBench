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
typedef  int /*<<< orphan*/  uint8_t ;
struct params_s {scalar_t__ packets_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT (int) ; 
 int OK ; 
 scalar_t__ xiph_CountLavcHeaders (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int test_xiph_CountLavcHeaders(const char *run,
                 const uint8_t *p_extra, size_t i_extra,
                 const struct params_s *source)
{
    EXPECT(xiph_CountLavcHeaders(p_extra, i_extra) == source->packets_count);
    return OK;
}