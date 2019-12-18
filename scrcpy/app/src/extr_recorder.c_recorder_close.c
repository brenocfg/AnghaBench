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
struct recorder {int failed; int /*<<< orphan*/  filename; int /*<<< orphan*/  format; TYPE_1__* ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  pb; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGI (char*,char const*,int /*<<< orphan*/ ) ; 
 int av_write_trailer (TYPE_1__*) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ ) ; 
 char* recorder_get_format_name (int /*<<< orphan*/ ) ; 

void
recorder_close(struct recorder *recorder) {
    int ret = av_write_trailer(recorder->ctx);
    if (ret < 0) {
        LOGE("Failed to write trailer to %s", recorder->filename);
        recorder->failed = true;
    }
    avio_close(recorder->ctx->pb);
    avformat_free_context(recorder->ctx);

    if (recorder->failed) {
        LOGE("Recording failed to %s", recorder->filename);
    } else {
        const char *format_name = recorder_get_format_name(recorder->format);
        LOGI("Recording complete to %s file: %s", format_name, recorder->filename);
    }
}