#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WebPInfoStatus ;
struct TYPE_8__ {int /*<<< orphan*/  quiet_; scalar_t__ show_summary_; } ;
typedef  TYPE_1__ WebPInfo ;
typedef  int /*<<< orphan*/  WebPData ;
typedef  int /*<<< orphan*/  MemBuffer ;
typedef  int /*<<< orphan*/  ChunkData ;

/* Variables and functions */
 int /*<<< orphan*/  InitMemBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ MemDataSize (int /*<<< orphan*/ *) ; 
 scalar_t__ ParseChunk (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ParseRIFFHeader (TYPE_1__* const,int /*<<< orphan*/ *) ; 
 scalar_t__ ProcessChunk (int /*<<< orphan*/ *,TYPE_1__* const) ; 
 int /*<<< orphan*/  ShowSummary (TYPE_1__* const) ; 
 scalar_t__ Validate (TYPE_1__* const) ; 
 scalar_t__ WEBP_INFO_OK ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static WebPInfoStatus AnalyzeWebP(WebPInfo* const webp_info,
                                  const WebPData* webp_data) {
  ChunkData chunk_data;
  MemBuffer mem_buffer;
  WebPInfoStatus webp_info_status = WEBP_INFO_OK;

  InitMemBuffer(&mem_buffer, webp_data);
  webp_info_status = ParseRIFFHeader(webp_info, &mem_buffer);
  if (webp_info_status != WEBP_INFO_OK) goto Error;

  //  Loop through all the chunks. Terminate immediately in case of error.
  while (webp_info_status == WEBP_INFO_OK && MemDataSize(&mem_buffer) > 0) {
    webp_info_status = ParseChunk(webp_info, &mem_buffer, &chunk_data);
    if (webp_info_status != WEBP_INFO_OK) goto Error;
    webp_info_status = ProcessChunk(&chunk_data, webp_info);
  }
  if (webp_info_status != WEBP_INFO_OK) goto Error;
  if (webp_info->show_summary_) ShowSummary(webp_info);

  //  Final check.
  webp_info_status = Validate(webp_info);

 Error:
  if (!webp_info->quiet_) {
    if (webp_info_status == WEBP_INFO_OK) {
      printf("No error detected.\n");
    } else {
      printf("Errors detected.\n");
    }
  }
  return webp_info_status;
}