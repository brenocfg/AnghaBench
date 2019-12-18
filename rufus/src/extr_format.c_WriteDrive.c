#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {scalar_t__ DiskSize; int SectorSize; } ;
struct TYPE_6__ {scalar_t__ image_size; scalar_t__ compression_type; } ;
struct TYPE_5__ {scalar_t__ QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ BLED_COMPRESSION_NONE ; 
 int /*<<< orphan*/  CHECK_FOR_USER_CANCEL ; 
 int DD_BUFFER_SIZE ; 
 scalar_t__ ERROR_CANCELLED ; 
 int ERROR_NOT_ENOUGH_MEMORY ; 
 int ERROR_READ_FAULT ; 
 int ERROR_SEVERITY_ERROR ; 
 int ERROR_WRITE_FAULT ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int FormatStatus ; 
 int /*<<< orphan*/  MSG_261 ; 
 int /*<<< orphan*/  MSG_286 ; 
 int /*<<< orphan*/  MSG_306 ; 
 int /*<<< orphan*/  OP_FORMAT ; 
 scalar_t__ ReadFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RefreshDriveLayout (int /*<<< orphan*/ *) ; 
 scalar_t__ SCODE_CODE (int) ; 
 TYPE_4__ SelectedDrive ; 
 int /*<<< orphan*/  SetFilePointerEx (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UpdateProgressWithInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  UpdateProgressWithInfoInit (int /*<<< orphan*/ *,scalar_t__) ; 
 int WRITE_RETRIES ; 
 int WRITE_TIMEOUT ; 
 int WindowsErrorString () ; 
 scalar_t__ WriteFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ _mm_malloc (scalar_t__,int) ; 
 int /*<<< orphan*/  _uprintf ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bled_exit () ; 
 int /*<<< orphan*/  bled_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ bled_uncompress_with_handles (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ fast_zeroing ; 
 TYPE_2__ img_report ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  safe_mm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_progress ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

__attribute__((used)) static BOOL WriteDrive(HANDLE hPhysicalDrive, HANDLE hSourceImage)
{
	BOOL s, ret = FALSE;
	LARGE_INTEGER li;
	DWORD rSize, wSize, xSize, BufSize;
	uint64_t wb, target_size = hSourceImage?img_report.image_size:SelectedDrive.DiskSize;
	int64_t bled_ret;
	uint8_t *buffer = NULL;
	uint8_t *cmp_buffer = NULL;
	int i, *ptr, zero_data, throttle_fast_zeroing = 0;

	// We poked the MBR and other stuff, so we need to rewind
	li.QuadPart = 0;
	if (!SetFilePointerEx(hPhysicalDrive, li, NULL, FILE_BEGIN))
		uprintf("Warning: Unable to rewind image position - wrong data might be copied!");
	UpdateProgressWithInfoInit(NULL, FALSE);

	if (img_report.compression_type != BLED_COMPRESSION_NONE) {
		uprintf("Writing compressed image...");
		bled_init(_uprintf, update_progress, &FormatStatus);
		bled_ret = bled_uncompress_with_handles(hSourceImage, hPhysicalDrive, img_report.compression_type);
		bled_exit();
		if ((bled_ret < 0) && (SCODE_CODE(FormatStatus) != ERROR_CANCELLED)) {
			// Unfortunately, different compression backends return different negative error codes
			uprintf("Could not write compressed image: %lld", bled_ret);
			FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | ERROR_WRITE_FAULT;
			goto out;
		}
	} else {
		uprintf(hSourceImage?"Writing Image...":fast_zeroing?"Fast-zeroing drive...":"Zeroing drive...");
		// Our buffer size must be a multiple of the sector size and *ALIGNED* to the sector size
		BufSize = ((DD_BUFFER_SIZE + SelectedDrive.SectorSize - 1) / SelectedDrive.SectorSize) * SelectedDrive.SectorSize;
		buffer = (uint8_t*)_mm_malloc(BufSize, SelectedDrive.SectorSize);
		if (buffer == NULL) {
			FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | ERROR_NOT_ENOUGH_MEMORY;
			uprintf("Could not allocate disk write buffer");
			goto out;
		}
		assert((uintptr_t)buffer % SelectedDrive.SectorSize == 0);

		// Clear buffer
		memset(buffer, fast_zeroing ? 0xff : 0x00, BufSize);

		cmp_buffer = (uint8_t*)_mm_malloc(BufSize, SelectedDrive.SectorSize);
		if (cmp_buffer == NULL) {
			FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | ERROR_NOT_ENOUGH_MEMORY;
			uprintf("Could not allocate disk comparison buffer");
			goto out;
		}
		assert((uintptr_t)cmp_buffer % SelectedDrive.SectorSize == 0);

		// Don't bother trying for something clever, using double buffering overlapped and whatnot:
		// With Windows' default optimizations, sync read + sync write for sequential operations
		// will be as fast, if not faster, than whatever async scheme you can come up with.
		rSize = BufSize;
		for (wb = 0, wSize = 0; wb < (uint64_t)SelectedDrive.DiskSize; wb += wSize) {
			UpdateProgressWithInfo(OP_FORMAT, hSourceImage ? MSG_261 : fast_zeroing ? MSG_306 : MSG_286, wb, target_size);
			if (hSourceImage != NULL) {
				s = ReadFile(hSourceImage, buffer, BufSize, &rSize, NULL);
				if (!s) {
					FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | ERROR_READ_FAULT;
					uprintf("Read error: %s", WindowsErrorString());
					goto out;
				}
				if (rSize == 0)
					break;
			}
			// Don't overflow our projected size (mostly for VHDs)
			if (wb + rSize > target_size) {
				rSize = (DWORD)(target_size - wb);
			}

			// WriteFile fails unless the size is a multiple of sector size
			if (rSize % SelectedDrive.SectorSize != 0)
				rSize = ((rSize + SelectedDrive.SectorSize - 1) / SelectedDrive.SectorSize) * SelectedDrive.SectorSize;

			// Fast-zeroing: Depending on your hardware, reading from flash may be much faster than writing, so
			// we might speed things up by skipping empty blocks, or skipping the write if the data is the same.
			// Notes: A block is declared empty when all bits are either 0 (zeros) or 1 (flash block erased).
			// Also, a back-off strategy is used to limit reading.
			if (throttle_fast_zeroing) {
				throttle_fast_zeroing--;
			} else if (fast_zeroing) {
				assert(hSourceImage == NULL);	// Only enabled for zeroing
				CHECK_FOR_USER_CANCEL;

				// Read block and compare against the block that needs to be written
				s = ReadFile(hPhysicalDrive, cmp_buffer, rSize, &xSize, NULL);
				if ((!s) || (xSize != rSize) ) {
					uprintf("Read error: Could not read data for comparison - %s", WindowsErrorString());
					goto out;
				}

				// Check for an empty block
				ptr = (int*)(cmp_buffer);
				// Get first element
				zero_data = ptr[0];
				// Check all bits are the same
				if ((zero_data == 0) || (zero_data == -1)) {
					// Compare the rest of the block against the first element
					for (i = 1; i < (int)(rSize / sizeof(int)); i++) {
						if (ptr[i] != zero_data)
							break;
					}
					if (i >= (int)(rSize / sizeof(int))) {
						// Block is empty, skip write
						wSize = rSize;
						continue;
					}
				}

				// Move the file pointer position back for writing
				li.QuadPart = wb;
				if (!SetFilePointerEx(hPhysicalDrive, li, NULL, FILE_BEGIN)) {
					uprintf("Error: Could not reset position - %s", WindowsErrorString());
					goto out;
				}
				// Throttle read operations
				throttle_fast_zeroing = 15;
			}

			for (i = 1; i <= WRITE_RETRIES; i++) {
				CHECK_FOR_USER_CANCEL;
				s = WriteFile(hPhysicalDrive, buffer, rSize, &wSize, NULL);
				if ((s) && (wSize == rSize))
					break;
				if (s)
					uprintf("Write error: Wrote %d bytes, expected %d bytes", wSize, rSize);
				else
					uprintf("Write error at sector %lld: %s", wb / SelectedDrive.SectorSize, WindowsErrorString());
				if (i < WRITE_RETRIES) {
					li.QuadPart = wb;
					uprintf("Retrying in %d seconds...", WRITE_TIMEOUT / 1000);
					Sleep(WRITE_TIMEOUT);
					if (!SetFilePointerEx(hPhysicalDrive, li, NULL, FILE_BEGIN)) {
						uprintf("Write error: Could not reset position - %s", WindowsErrorString());
						goto out;
					}
				} else {
					FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | ERROR_WRITE_FAULT;
					goto out;
				}
				Sleep(200);
			}
			if (i > WRITE_RETRIES)
				goto out;
		}
	}
	RefreshDriveLayout(hPhysicalDrive);
	ret = TRUE;
out:
	safe_mm_free(buffer);
	safe_mm_free(cmp_buffer);
	return ret;
}