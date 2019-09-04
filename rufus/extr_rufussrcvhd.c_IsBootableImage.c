#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ checksum; scalar_t__ disk_type; scalar_t__ file_format_version; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_1__ vhd_footer ;
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ compression_type; int image_size; int /*<<< orphan*/  is_vhd; } ;
struct TYPE_9__ {int QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOLEAN ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ AnalyzeMBR (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ BLED_COMPRESSION_NONE ; 
 scalar_t__ CreateFileU (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetFileSizeEx (scalar_t__,TYPE_2__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IsCompressedBootableImage (char const*) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,TYPE_1__*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFilePointerEx (scalar_t__,TYPE_2__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VHD_FOOTER_FILE_FORMAT_V1_0 ; 
 scalar_t__ VHD_FOOTER_TYPE_FIXED_HARD_DISK ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 scalar_t__ bswap_uint32 (scalar_t__) ; 
 int /*<<< orphan*/  conectix_str ; 
 TYPE_4__ img_report ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int /*<<< orphan*/  safe_free (TYPE_1__*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

BOOL IsBootableImage(const char* path)
{
	HANDLE handle = INVALID_HANDLE_VALUE;
	LARGE_INTEGER liImageSize;
	vhd_footer* footer = NULL;
	DWORD size;
	size_t i;
	uint32_t checksum, old_checksum;
	LARGE_INTEGER ptr;
	BOOL is_bootable_img = FALSE;

	uprintf("Disk image analysis:");
	handle = CreateFileU(path, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handle == INVALID_HANDLE_VALUE) {
		uprintf("  Could not open image '%s'", path);
		goto out;
	}

	is_bootable_img = (BOOLEAN)IsCompressedBootableImage(path);
	if (img_report.compression_type == BLED_COMPRESSION_NONE)
		is_bootable_img = (BOOLEAN)AnalyzeMBR(handle, "  Image", FALSE);

	if (!GetFileSizeEx(handle, &liImageSize)) {
		uprintf("  Could not get image size: %s", WindowsErrorString());
		goto out;
	}
	img_report.image_size = (uint64_t)liImageSize.QuadPart;

	size = sizeof(vhd_footer);
	if ((img_report.compression_type == BLED_COMPRESSION_NONE) && (img_report.image_size >= (512 + size))) {
		footer = (vhd_footer*)malloc(size);
		ptr.QuadPart = img_report.image_size - size;
		if ( (footer == NULL) || (!SetFilePointerEx(handle, ptr, NULL, FILE_BEGIN)) ||
			 (!ReadFile(handle, footer, size, &size, NULL)) || (size != sizeof(vhd_footer)) ) {
			uprintf("  Could not read VHD footer");
			goto out;
		}
		if (memcmp(footer->cookie, conectix_str, sizeof(footer->cookie)) == 0) {
			img_report.image_size -= sizeof(vhd_footer);
			if ( (bswap_uint32(footer->file_format_version) != VHD_FOOTER_FILE_FORMAT_V1_0)
			  || (bswap_uint32(footer->disk_type) != VHD_FOOTER_TYPE_FIXED_HARD_DISK)) {
				uprintf("  Unsupported type of VHD image");
				is_bootable_img = FALSE;
				goto out;
			}
			// Might as well validate the checksum while we're at it
			old_checksum = bswap_uint32(footer->checksum);
			footer->checksum = 0;
			for (checksum=0, i=0; i<sizeof(vhd_footer); i++)
				checksum += ((uint8_t*)footer)[i];
			checksum = ~checksum;
			if (checksum != old_checksum)
				uprintf("  Warning: VHD footer seems corrupted (checksum: %04X, expected: %04X)", old_checksum, checksum);
			// Need to remove the footer from our payload
			uprintf("  Image is a Fixed Hard Disk VHD file");
			img_report.is_vhd = TRUE;
		}
	}

out:
	safe_free(footer);
	safe_closehandle(handle);
	return is_bootable_img;
}