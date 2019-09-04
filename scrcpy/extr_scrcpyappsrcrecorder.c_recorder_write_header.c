#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct recorder {TYPE_5__* ctx; int /*<<< orphan*/  filename; } ;
struct TYPE_10__ {int /*<<< orphan*/  pb; TYPE_2__** streams; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__* codec; } ;
struct TYPE_7__ {int extradata_size; int /*<<< orphan*/ * extradata; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  LOGC (char*) ; 
 int /*<<< orphan*/  LOGE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_5__*) ; 
 int avformat_write_header (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_closep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
recorder_write_header(struct recorder *recorder, const AVPacket *packet) {
    AVStream *ostream = recorder->ctx->streams[0];

    uint8_t *extradata = av_malloc(packet->size * sizeof(uint8_t));
    if (!extradata) {
        LOGC("Cannot allocate extradata");
        return false;
    }

    // copy the first packet to the extra data
    memcpy(extradata, packet->data, packet->size);

#ifdef SCRCPY_LAVF_HAS_NEW_CODEC_PARAMS_API
    ostream->codecpar->extradata = extradata;
    ostream->codecpar->extradata_size = packet->size;
#else
    ostream->codec->extradata = extradata;
    ostream->codec->extradata_size = packet->size;
#endif

    int ret = avformat_write_header(recorder->ctx, NULL);
    if (ret < 0) {
        LOGE("Failed to write header to %s", recorder->filename);
        SDL_free(extradata);
        avio_closep(&recorder->ctx->pb);
        avformat_free_context(recorder->ctx);
        return false;
    }

    return true;
}