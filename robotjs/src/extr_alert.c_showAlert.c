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
typedef  scalar_t__ SInt32 ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  scalar_t__ CFOptionFlags ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFStringCreateWithUTF8String (char const*) ; 
 scalar_t__ CFUserNotificationDisplayAlert (double,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int EXEC_FAILED ; 
 int IDOK ; 
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MB_OKCANCEL ; 
 int MessageBox (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int TASK_SUCCESS ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kCFUserNotificationDefaultResponse ; 
 int /*<<< orphan*/  kCFUserNotificationNoteAlertLevel ; 
 int /*<<< orphan*/  stderr ; 
 int xmessage (char**,int*) ; 

int showAlert(const char *title, const char *msg, const char *defaultButton,
              const char *cancelButton)
{
#if defined(IS_MACOSX)
	CFStringRef alertHeader = CFStringCreateWithUTF8String(title);
	CFStringRef alertMessage = CFStringCreateWithUTF8String(msg);
	CFStringRef defaultButtonTitle = CFStringCreateWithUTF8String(defaultButton);
	CFStringRef cancelButtonTitle = CFStringCreateWithUTF8String(cancelButton);
	CFOptionFlags responseFlags;
	SInt32 err = CFUserNotificationDisplayAlert(0.0,
	                                            kCFUserNotificationNoteAlertLevel,
	                                            NULL,
	                                            NULL,
	                                            NULL,
	                                            alertHeader,
	                                            alertMessage,
	                                            defaultButtonTitle,
	                                            cancelButtonTitle,
	                                            NULL,
	                                            &responseFlags);
	if (alertHeader != NULL) CFRelease(alertHeader);
	if (alertMessage != NULL) CFRelease(alertMessage);
	if (defaultButtonTitle != NULL) CFRelease(defaultButtonTitle);
	if (cancelButtonTitle != NULL) CFRelease(cancelButtonTitle);

	if (err != 0) return -1;
	return (responseFlags == kCFUserNotificationDefaultResponse) ? 0 : 1;
#elif defined(USE_X11)
	/* Note that args[0] is set by the xmessage() function. */
	const char *args[10] = {NULL, msg, "-title", title, "-center"};
	int response, ret;
	char *buttonList = NULL; /* To be free()'d. */

	if (defaultButton == NULL) defaultButton = "OK";

	if (cancelButton == NULL) {
		asprintf(&buttonList, "%s:2", defaultButton);
	} else {
		asprintf(&buttonList, "%s:2,%s:3", defaultButton, cancelButton);
	}

	if (buttonList == NULL) return -1; /* asprintf() failed. */
	args[5] = "-buttons";
	args[6] = buttonList;
	args[7] = "-default";
	args[8] = defaultButton;
	args[9] = NULL;

	ret = xmessage((char **)args, &response);
	if (buttonList != NULL) {
		free(buttonList);
		buttonList = NULL;
	}

	if (ret != TASK_SUCCESS) {
		if (ret == EXEC_FAILED) {
			fputs("xmessage or equivalent not found.\n", stderr);
		}
		return -1;
	}

	return (response == 2) ? 0 : 1;
#else
	/* TODO: Display custom buttons instead of the pre-defined "OK"
	 * and "Cancel". */
	int response = MessageBox(NULL, msg, title,
	                          (cancelButton == NULL) ? MB_OK : MB_OKCANCEL);
	return (response == IDOK) ? 0 : 1;
#endif
}