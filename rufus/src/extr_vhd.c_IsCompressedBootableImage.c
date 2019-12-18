#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  ext; } ;
struct TYPE_4__ {int /*<<< orphan*/  compression_type; } ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAYSIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  BLED_COMPRESSION_NONE ; 
 int FALSE ; 
 scalar_t__ FormatStatus ; 
 scalar_t__ MBR_SIZE ; 
 int /*<<< orphan*/  _uprintf ; 
 int /*<<< orphan*/  bled_exit () ; 
 int /*<<< orphan*/  bled_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ bled_uncompress_to_buffer (char const*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* file_assoc ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 TYPE_1__ img_report ; 
 unsigned char* malloc (scalar_t__) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

BOOL IsCompressedBootableImage(const char* path)
{
	char *p;
	unsigned char *buf = NULL;
	int i;
	BOOL r = FALSE;
	int64_t dc;

	img_report.compression_type = BLED_COMPRESSION_NONE;
	for (p = (char*)&path[strlen(path)-1]; (*p != '.') && (p != path); p--);

	if (p == path)
		return FALSE;

	for (i = 0; i<ARRAYSIZE(file_assoc); i++) {
		if (strcmp(p, file_assoc[i].ext) == 0) {
			img_report.compression_type = file_assoc[i].type;
			buf = malloc(MBR_SIZE);
			if (buf == NULL)
				return FALSE;
			FormatStatus = 0;
			bled_init(_uprintf, NULL, &FormatStatus);
			dc = bled_uncompress_to_buffer(path, (char*)buf, MBR_SIZE, file_assoc[i].type);
			bled_exit();
			if (dc != MBR_SIZE) {
				free(buf);
				return FALSE;
			}
			r = (buf[0x1FE] == 0x55) && (buf[0x1FF] == 0xAA);
			free(buf);
			return r;
		}
	}

	return FALSE;
}