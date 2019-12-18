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
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_AVI_RES ; 
 int /*<<< orphan*/  TEST_SOUND_AVI_RES ; 
 int /*<<< orphan*/  test_avi_filename ; 
 int /*<<< orphan*/  test_sound_avi_filename ; 
 scalar_t__ unpack_avi_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL init_tests(void)
{
    return unpack_avi_file(TEST_AVI_RES, test_avi_filename)
        && unpack_avi_file(TEST_SOUND_AVI_RES, test_sound_avi_filename);
}