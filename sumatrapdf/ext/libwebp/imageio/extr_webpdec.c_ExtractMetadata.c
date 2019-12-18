#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  WebPDemuxer ;
struct TYPE_10__ {size_t member_1; int /*<<< orphan*/  const* const member_0; } ;
typedef  TYPE_2__ WebPData ;
struct TYPE_9__ {int /*<<< orphan*/  size; scalar_t__ bytes; } ;
struct TYPE_11__ {TYPE_1__ chunk; } ;
typedef  TYPE_3__ WebPChunkIterator ;
struct TYPE_12__ {int /*<<< orphan*/  xmp; int /*<<< orphan*/  exif; int /*<<< orphan*/  iccp; } ;
typedef  TYPE_4__ Metadata ;

/* Variables and functions */
 int EXIF_FLAG ; 
 int ICCP_FLAG ; 
 int /*<<< orphan*/  MetadataCopy (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEBP_FF_FORMAT_FLAGS ; 
 int /*<<< orphan*/ * WebPDemux (TYPE_2__*) ; 
 int /*<<< orphan*/  WebPDemuxDelete (int /*<<< orphan*/ * const) ; 
 scalar_t__ WebPDemuxGetChunk (int /*<<< orphan*/ * const,char*,int,TYPE_3__*) ; 
 int WebPDemuxGetI (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPDemuxReleaseChunkIterator (TYPE_3__*) ; 
 int XMP_FLAG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ExtractMetadata(const uint8_t* const data, size_t data_size,
                           Metadata* const metadata) {
  WebPData webp_data = { data, data_size };
  WebPDemuxer* const demux = WebPDemux(&webp_data);
  WebPChunkIterator chunk_iter;
  uint32_t flags;

  if (demux == NULL) return 0;
  assert(metadata != NULL);

  flags = WebPDemuxGetI(demux, WEBP_FF_FORMAT_FLAGS);

  if ((flags & ICCP_FLAG) && WebPDemuxGetChunk(demux, "ICCP", 1, &chunk_iter)) {
    MetadataCopy((const char*)chunk_iter.chunk.bytes, chunk_iter.chunk.size,
                 &metadata->iccp);
    WebPDemuxReleaseChunkIterator(&chunk_iter);
  }
  if ((flags & EXIF_FLAG) && WebPDemuxGetChunk(demux, "EXIF", 1, &chunk_iter)) {
    MetadataCopy((const char*)chunk_iter.chunk.bytes, chunk_iter.chunk.size,
                 &metadata->exif);
    WebPDemuxReleaseChunkIterator(&chunk_iter);
  }
  if ((flags & XMP_FLAG) && WebPDemuxGetChunk(demux, "XMP ", 1, &chunk_iter)) {
    MetadataCopy((const char*)chunk_iter.chunk.bytes, chunk_iter.chunk.size,
                 &metadata->xmp);
    WebPDemuxReleaseChunkIterator(&chunk_iter);
  }
  WebPDemuxDelete(demux);
  return 1;
}