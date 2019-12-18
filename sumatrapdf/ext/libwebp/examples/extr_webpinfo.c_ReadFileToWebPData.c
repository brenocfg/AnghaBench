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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t size; int /*<<< orphan*/  const* bytes; } ;
typedef  TYPE_1__ WebPData ;

/* Variables and functions */
 int /*<<< orphan*/  ImgIoUtilReadFile (char const* const,int /*<<< orphan*/  const**,size_t*) ; 

__attribute__((used)) static int ReadFileToWebPData(const char* const filename,
                              WebPData* const webp_data) {
  const uint8_t* data;
  size_t size;
  if (!ImgIoUtilReadFile(filename, &data, &size)) return 0;
  webp_data->bytes = data;
  webp_data->size = size;
  return 1;
}