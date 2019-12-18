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
#define  RECORDER_FORMAT_MKV 129 
#define  RECORDER_FORMAT_MP4 128 

__attribute__((used)) static const char *
recorder_get_format_name(enum recorder_format format) {
    switch (format) {
        case RECORDER_FORMAT_MP4: return "mp4";
        case RECORDER_FORMAT_MKV: return "matroska";
        default: return NULL;
    }
}