#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_9__ {TYPE_2__ xmp; TYPE_1__ exif; TYPE_3__ iccp; } ;
typedef  TYPE_4__ Metadata ;

/* Variables and functions */
 int METADATA_EXIF ; 
 int METADATA_ICC ; 
 int METADATA_XMP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void PrintMetadataInfo(const Metadata* const metadata,
                              int metadata_written) {
  if (metadata == NULL || metadata_written == 0) return;

  fprintf(stderr, "Metadata:\n");
  if (metadata_written & METADATA_ICC) {
    fprintf(stderr, "  * ICC profile:  %6d bytes\n", (int)metadata->iccp.size);
  }
  if (metadata_written & METADATA_EXIF) {
    fprintf(stderr, "  * EXIF data:    %6d bytes\n", (int)metadata->exif.size);
  }
  if (metadata_written & METADATA_XMP) {
    fprintf(stderr, "  * XMP data:     %6d bytes\n", (int)metadata->xmp.size);
  }
}