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
typedef  enum recorder_format { ____Placeholder_recorder_format } recorder_format ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*,char const*) ; 
 int RECORDER_FORMAT_MKV ; 
 int RECORDER_FORMAT_MP4 ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool
parse_record_format(const char *optarg, enum recorder_format *format) {
    if (!strcmp(optarg, "mp4")) {
        *format = RECORDER_FORMAT_MP4;
        return true;
    }
    if (!strcmp(optarg, "mkv")) {
        *format = RECORDER_FORMAT_MKV;
        return true;
    }
    LOGE("Unsupported format: %s (expected mp4 or mkv)", optarg);
    return false;
}