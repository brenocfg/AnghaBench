#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
struct TYPE_4__ {int* proposed_label; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_label; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_2__ SelectedDrive ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  free (int*) ; 
 TYPE_1__ img_report ; 
 int /*<<< orphan*/  safe_strcpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int toupper (int) ; 
 int /*<<< orphan*/  uprintf (char*,int*) ; 
 int* utf8_to_wchar (char*) ; 
 int /*<<< orphan*/  wchar_to_utf8_no_alloc (int*,int /*<<< orphan*/ ,int) ; 
 int wcslen (int*) ; 

__attribute__((used)) static void ToValidLabel(char* Label, BOOL bFAT)
{
	size_t i, j, k;
	BOOL found;
	WCHAR unauthorized[] = L"*?,;:/\\|+=<>[]\"";
	WCHAR to_underscore[] = L"\t.";
	WCHAR *wLabel = utf8_to_wchar(Label);

	if (wLabel == NULL)
		return;

	for (i = 0, k = 0; i < wcslen(wLabel); i++) {
		if (bFAT) {	// NTFS does allows all the FAT unauthorized above
			found = FALSE;
			for (j = 0; j < wcslen(unauthorized); j++) {
				if (wLabel[i] == unauthorized[j]) {
					found = TRUE;
					break;
				}
			}
			// A FAT label that contains extended chars will be rejected
			if (wLabel[i] >= 0x80) {
				wLabel[k++] = L'_';
				found = TRUE;
			}
			if (found)
				continue;
		}
		found = FALSE;
		for (j = 0; j < wcslen(to_underscore); j++) {
			if (wLabel[i] == to_underscore[j]) {
				wLabel[k++] = '_';
				found = TRUE;
				break;
			}
		}
		if (found)
			continue;
		wLabel[k++] = bFAT ? toupper(wLabel[i]) : wLabel[i];
	}
	wLabel[k] = 0;

	if (bFAT) {
		if (wcslen(wLabel) > 11)
			wLabel[11] = 0;
		for (i = 0, j = 0; wLabel[i] != 0 ; i++)
			if (wLabel[i] == '_')
				j++;
		if (i < 2*j) {
			// If the final label is mostly underscore, use the proposed label
			uprintf("FAT label is mostly underscores. Using '%s' label instead.", SelectedDrive.proposed_label);
			for(i = 0; SelectedDrive.proposed_label[i] != 0; i++)
				wLabel[i] = SelectedDrive.proposed_label[i];
			wLabel[i] = 0;
		}
	} else if (wcslen(wLabel) > 32) {
		wLabel[32] = 0;
	}

	// Needed for disk by label isolinux.cfg workaround
	wchar_to_utf8_no_alloc(wLabel, img_report.usb_label, sizeof(img_report.usb_label));
	safe_strcpy(Label, strlen(Label) + 1, img_report.usb_label);
	free(wLabel);
}