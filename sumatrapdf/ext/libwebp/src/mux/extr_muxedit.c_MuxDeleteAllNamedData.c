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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMux ;
typedef  int /*<<< orphan*/  WebPChunkId ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkGetIdFromTag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteChunks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsWPI (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MuxGetChunkListFromId (int /*<<< orphan*/ * const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  WEBP_MUX_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WebPMuxError MuxDeleteAllNamedData(WebPMux* const mux, uint32_t tag) {
  const WebPChunkId id = ChunkGetIdFromTag(tag);
  assert(mux != NULL);
  if (IsWPI(id)) return WEBP_MUX_INVALID_ARGUMENT;
  return DeleteChunks(MuxGetChunkListFromId(mux, id), tag);
}