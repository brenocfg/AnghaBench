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
typedef  int /*<<< orphan*/  MMPasteError ;
typedef  int /*<<< orphan*/  MMBitmapRef ;

/* Variables and functions */

MMPasteError copyMMBitmapToPasteboard(MMBitmapRef bitmap)
{
#if defined(IS_MACOSX)
	PasteboardRef clipboard;

	size_t len;
	uint8_t *pngbuf;
	CFDataRef data;
	OSStatus err;

	if (PasteboardCreate(kPasteboardClipboard, &clipboard) != noErr) {
		return kMMPasteOpenError;
	}

	if (PasteboardClear(clipboard) != noErr) {
		CFRelease(clipboard);
		return kMMPasteClearError;
	}

	pngbuf = createPNGData(bitmap, &len);
	if (pngbuf == NULL) {
		CFRelease(clipboard);
		return kMMPasteDataError;
	}

	data = CFDataCreateWithBytesNoCopy(kCFAllocatorDefault, pngbuf, len,
	                                   kCFAllocatorNull);
	if (data == NULL) {
		CFRelease(clipboard);
		free(pngbuf);
		return kMMPasteDataError;
	}

	err = PasteboardPutItemFlavor(clipboard, bitmap, kUTTypePNG, data, 0);
	CFRelease(data);
	CFRelease(clipboard);
	free(pngbuf);
	return (err == noErr) ? kMMPasteNoError : kMMPastePasteError;
#elif defined(IS_WINDOWS)
	MMPasteError ret = kMMPasteNoError;
	uint8_t *bmpData;
	size_t len;
	HGLOBAL handle;

	if (!OpenClipboard(NULL)) return kMMPasteOpenError;
	if (!EmptyClipboard()) return kMMPasteClearError;

	bmpData = createBitmapData(bitmap, &len);
	if (bmpData == NULL) return kMMPasteDataError;

	/* CF_DIB does not include the BITMAPFILEHEADER struct (and displays a
	 * cryptic error if it is included). */
	len -= sizeof(BITMAPFILEHEADER);

	/* SetClipboardData() needs a "handle", not just a buffer, so we have to
	 * allocate one with GlobalAlloc(). */
	if ((handle = GlobalAlloc(GMEM_MOVEABLE, len)) == NULL) {
		CloseClipboard();
		free(bmpData);
		return kMMPasteDataError;
	}

	memcpy(GlobalLock(handle), bmpData + sizeof(BITMAPFILEHEADER), len);
	GlobalUnlock(handle);
	free(bmpData);

	if (SetClipboardData(CF_DIB, handle) == NULL) {
		ret = kMMPastePasteError;
	}

	CloseClipboard();
	GlobalFree(handle);
	return ret;
#elif defined(USE_X11)
	/* TODO (X11's clipboard is _weird_.) */
	return kMMPasteUnsupportedError;
#endif
}