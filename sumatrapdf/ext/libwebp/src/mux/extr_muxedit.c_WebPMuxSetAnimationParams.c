#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_6__ {int /*<<< orphan*/  loop_count; int /*<<< orphan*/  bgcolor; } ;
typedef  TYPE_1__ WebPMuxAnimParams ;
typedef  int /*<<< orphan*/  WebPMux ;
struct TYPE_7__ {int member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ WebPData ;
struct TYPE_8__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int ANIM_CHUNK_SIZE ; 
 size_t IDX_ANIM ; 
 int /*<<< orphan*/  MAX_LOOP_COUNT ; 
 scalar_t__ MuxDeleteAllNamedData (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MuxSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  PutLE16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutLE32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_NOT_FOUND ; 
 scalar_t__ WEBP_MUX_OK ; 
 TYPE_3__* kChunks ; 

WebPMuxError WebPMuxSetAnimationParams(WebPMux* mux,
                                       const WebPMuxAnimParams* params) {
  WebPMuxError err;
  uint8_t data[ANIM_CHUNK_SIZE];
  const WebPData anim = { data, ANIM_CHUNK_SIZE };

  if (mux == NULL || params == NULL) return WEBP_MUX_INVALID_ARGUMENT;
  if (params->loop_count < 0 || params->loop_count >= MAX_LOOP_COUNT) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }

  // Delete any existing ANIM chunk(s).
  err = MuxDeleteAllNamedData(mux, kChunks[IDX_ANIM].tag);
  if (err != WEBP_MUX_OK && err != WEBP_MUX_NOT_FOUND) return err;

  // Set the animation parameters.
  PutLE32(data, params->bgcolor);
  PutLE16(data + 4, params->loop_count);
  return MuxSet(mux, kChunks[IDX_ANIM].tag, &anim, 1);
}