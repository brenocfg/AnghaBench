#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int bytes_per_px; int depth; int max_value; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  data_size; int /*<<< orphan*/ * data; scalar_t__ seen_flags; } ;
typedef  TYPE_1__ PNMInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LINE_SIZE ; 
 size_t ReadLine (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,char*,size_t*) ; 
 size_t ReadPAMFields (TYPE_1__* const,size_t) ; 
 int /*<<< orphan*/  kMinPNMHeaderSize ; 
 int sscanf (char*,char*,int*,...) ; 

__attribute__((used)) static size_t ReadHeader(PNMInfo* const info) {
  size_t off = 0;
  char out[MAX_LINE_SIZE + 1];
  size_t out_size;
  if (info == NULL) return 0;
  if (info->data == NULL || info->data_size < kMinPNMHeaderSize) return 0;

  info->width = info->height = 0;
  info->type = -1;
  info->seen_flags = 0;
  info->bytes_per_px = 0;
  info->depth = 0;
  info->max_value = 0;

  off = ReadLine(info->data, off, info->data_size, out, &out_size);
  if (off == 0 || sscanf(out, "P%d", &info->type) != 1) return 0;
  if (info->type == 7) {
    off = ReadPAMFields(info, off);
  } else {
    off = ReadLine(info->data, off, info->data_size, out, &out_size);
    if (off == 0 || sscanf(out, "%d %d", &info->width, &info->height) != 2) {
      return 0;
    }
    off = ReadLine(info->data, off, info->data_size, out, &out_size);
    if (off == 0 || sscanf(out, "%d", &info->max_value) != 1) return 0;

    // finish initializing missing fields
    info->depth = (info->type == 5) ? 1 : 3;
  }
  // perform some basic numerical validation
  if (info->width <= 0 || info->height <= 0 ||
      info->type <= 0 || info->type >= 9 ||
      info->depth <= 0 || info->depth == 2 || info->depth > 4 ||
      info->max_value <= 0 || info->max_value >= 65536) {
    return 0;
  }
  info->bytes_per_px = info->depth * (info->max_value > 255 ? 2 : 1);
  return off;
}