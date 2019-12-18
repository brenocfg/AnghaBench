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
typedef  int /*<<< orphan*/  vorb ;

/* Variables and functions */
 int /*<<< orphan*/  VORBIS_missing_capture_pattern ; 
 int /*<<< orphan*/  capture_pattern (int /*<<< orphan*/ *) ; 
 int error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int start_page_no_capturepattern (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_page(vorb *f)
{
   if (!capture_pattern(f)) return error(f, VORBIS_missing_capture_pattern);
   return start_page_no_capturepattern(f);
}