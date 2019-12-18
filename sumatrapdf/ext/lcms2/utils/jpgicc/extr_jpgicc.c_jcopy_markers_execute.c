#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* jpeg_saved_marker_ptr ;
typedef  TYPE_2__* j_decompress_ptr ;
typedef  TYPE_3__* j_compress_ptr ;
struct TYPE_9__ {scalar_t__ write_Adobe_marker; scalar_t__ write_JFIF_header; } ;
struct TYPE_8__ {TYPE_1__* marker_list; } ;
struct TYPE_7__ {scalar_t__ marker; int data_length; int /*<<< orphan*/ * data; struct TYPE_7__* next; } ;

/* Variables and functions */
 int GETJOCTET (int /*<<< orphan*/ ) ; 
 scalar_t__ JPEG_APP0 ; 
 int /*<<< orphan*/  jpeg_write_marker (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
void jcopy_markers_execute(j_decompress_ptr srcinfo, j_compress_ptr dstinfo)
{
  jpeg_saved_marker_ptr marker;

  /* In the current implementation, we don't actually need to examine the
   * option flag here; we just copy everything that got saved.
   * But to avoid confusion, we do not output JFIF and Adobe APP14 markers
   * if the encoder library already wrote one.
   */
  for (marker = srcinfo->marker_list; marker != NULL; marker = marker->next) {

    if (dstinfo->write_JFIF_header &&
        marker->marker == JPEG_APP0 &&
        marker->data_length >= 5 &&
        GETJOCTET(marker->data[0]) == 0x4A &&
        GETJOCTET(marker->data[1]) == 0x46 &&
        GETJOCTET(marker->data[2]) == 0x49 &&
        GETJOCTET(marker->data[3]) == 0x46 &&
        GETJOCTET(marker->data[4]) == 0)
                          continue;         /* reject duplicate JFIF */

    if (dstinfo->write_Adobe_marker &&
        marker->marker == JPEG_APP0+14 &&
        marker->data_length >= 5 &&
        GETJOCTET(marker->data[0]) == 0x41 &&
        GETJOCTET(marker->data[1]) == 0x64 &&
        GETJOCTET(marker->data[2]) == 0x6F &&
        GETJOCTET(marker->data[3]) == 0x62 &&
        GETJOCTET(marker->data[4]) == 0x65)
                         continue;         /* reject duplicate Adobe */

     jpeg_write_marker(dstinfo, marker->marker,
                       marker->data, marker->data_length);
  }
}