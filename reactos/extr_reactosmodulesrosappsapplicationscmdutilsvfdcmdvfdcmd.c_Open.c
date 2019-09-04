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
typedef  scalar_t__ VFD_MEDIA ;
typedef  int /*<<< orphan*/  VFD_FLAGS ;
typedef  scalar_t__ VFD_FILETYPE ;
typedef  scalar_t__ VFD_DISKTYPE ;
typedef  char* ULONG ;
typedef  char* PCSTR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  char CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CheckDriver () ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ERROR_FILE_EXISTS ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_NOT_READY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_WRITE_PROTECT ; 
 scalar_t__ FALSE ; 
 scalar_t__ FILE_ATTRIBUTE_COMPRESSED ; 
 scalar_t__ FILE_ATTRIBUTE_ENCRYPTED ; 
 scalar_t__ FILE_ATTRIBUTE_READONLY ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 char InputChar (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ Install (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ACCESS_NG ; 
 int /*<<< orphan*/  MSG_CREATE144_CONFIRM ; 
 int /*<<< orphan*/  MSG_CREATE144_NOTICE ; 
 int /*<<< orphan*/  MSG_CREATE_CONFIRM ; 
 int /*<<< orphan*/  MSG_CREATE_NG ; 
 int /*<<< orphan*/  MSG_CREATE_NOTICE ; 
 int /*<<< orphan*/  MSG_DEFAULT_PROTECT ; 
 int /*<<< orphan*/  MSG_DRIVE_BUSY ; 
 int /*<<< orphan*/  MSG_DUPLICATE_ARGS ; 
 int /*<<< orphan*/  MSG_FILE_CREATED ; 
 int /*<<< orphan*/  MSG_FILE_MEDIA_UNKNOWN ; 
 int /*<<< orphan*/  MSG_GET_MEDIA_NG ; 
 int /*<<< orphan*/  MSG_HINT_OPEN ; 
 int /*<<< orphan*/  MSG_IMAGE_TOO_SMALL ; 
 int /*<<< orphan*/  MSG_MEDIATYPE_CONFIRM ; 
 int /*<<< orphan*/  MSG_MEDIATYPE_NOTICE ; 
 int /*<<< orphan*/  MSG_MEDIATYPE_SUGGEST ; 
 int /*<<< orphan*/  MSG_NO_MATCHING_MEDIA ; 
 int /*<<< orphan*/  MSG_OPEN_NG ; 
 int /*<<< orphan*/  MSG_OVERWRITE_CONFIRM ; 
 int /*<<< orphan*/  MSG_OVERWRITE_NOTICE ; 
 int /*<<< orphan*/  MSG_RAM_MEDIA_UNKNOWN ; 
 int /*<<< orphan*/  MSG_RAM_MODE_CONFIRM ; 
 int /*<<< orphan*/  MSG_RAM_MODE_NOTICE ; 
 int /*<<< orphan*/  MSG_RAM_MODE_ONLY ; 
 int /*<<< orphan*/  MSG_TARGET_NOTICE ; 
 int /*<<< orphan*/  MSG_UNKNOWN_OPTION ; 
 int OPERATION_ASK ; 
 int OPERATION_FORCE ; 
 int OPERATION_QUIT ; 
 int /*<<< orphan*/  PrintImageInfo (scalar_t__) ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,...) ; 
 scalar_t__ SERVICE_RUNNING ; 
 scalar_t__ Start (int /*<<< orphan*/ *) ; 
 char* SystemError (scalar_t__) ; 
 char* TARGET_NONE ; 
 scalar_t__ TRUE ; 
 scalar_t__ VFD_DISKTYPE_FILE ; 
 scalar_t__ VFD_DISKTYPE_RAM ; 
 int /*<<< orphan*/  VFD_FILETYPE_RAW ; 
 scalar_t__ VFD_FILETYPE_ZIP ; 
 int /*<<< orphan*/  VFD_FLAG_WRITE_PROTECTED ; 
 scalar_t__ VFD_MEDIA_F3_1P2 ; 
 scalar_t__ VFD_MEDIA_F3_1P4 ; 
 scalar_t__ VFD_MEDIA_F3_1P6 ; 
 scalar_t__ VFD_MEDIA_F3_1P7 ; 
 scalar_t__ VFD_MEDIA_F3_2P8 ; 
 scalar_t__ VFD_MEDIA_F3_640 ; 
 scalar_t__ VFD_MEDIA_F3_720 ; 
 scalar_t__ VFD_MEDIA_F3_820 ; 
 scalar_t__ VFD_MEDIA_F5_160 ; 
 scalar_t__ VFD_MEDIA_F5_180 ; 
 scalar_t__ VFD_MEDIA_F5_320 ; 
 scalar_t__ VFD_MEDIA_F5_360 ; 
 scalar_t__ VFD_MEDIA_NONE ; 
 int VFD_NG ; 
 scalar_t__ VFD_NOT_INSTALLED ; 
 scalar_t__ VFD_OK ; 
 scalar_t__ VfdCheckImageFile (char*,scalar_t__*,scalar_t__*,char**) ; 
 int /*<<< orphan*/  VfdChooseLetter () ; 
 scalar_t__ VfdCreateImageFile (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VfdGetGlobalLink (scalar_t__,char*) ; 
 int /*<<< orphan*/  VfdGetLocalLink (scalar_t__,char*) ; 
 scalar_t__ VfdGetMediaSize (scalar_t__) ; 
 scalar_t__ VfdGetMediaState (scalar_t__) ; 
 scalar_t__ VfdLookupMedia (char*) ; 
 int /*<<< orphan*/  VfdMediaTypeName (scalar_t__) ; 
 scalar_t__ VfdOpenDevice (char*) ; 
 scalar_t__ VfdOpenImage (scalar_t__,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VfdSetLocalLink (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ _stricmp (char const*,char*) ; 
 scalar_t__ driver_state ; 
 char* help_progname ; 
 scalar_t__ isalnum (char const) ; 
 int /*<<< orphan*/  isalpha (char) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* toupper (char const) ; 

int	Open(const char **args)
{
	int				mode		= OPERATION_ASK;
	BOOL			create		= FALSE;
	ULONG			target		= TARGET_NONE;
	PCSTR			file_name	= NULL;
	VFD_DISKTYPE	disk_type	= VFD_DISKTYPE_FILE;
	CHAR			protect		= '\0';
	VFD_MEDIA		media_type	= VFD_MEDIA_NONE;
	BOOL			five_inch	= FALSE;
	VFD_FLAGS		media_flags	= 0;
	HANDLE			hDevice;
	CHAR			letter;
	DWORD			ret;

	//	process parameters

	while (args && *args) {

		if (!_stricmp(*args, "/f") ||
			!_stricmp(*args, "/force")) {

			if (mode != OPERATION_ASK) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			mode = OPERATION_FORCE;
		}
		else if (!_stricmp(*args, "/q") ||
			!_stricmp(*args, "/quit")) {

			if (mode != OPERATION_ASK) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			mode = OPERATION_QUIT;
		}

		else if (!_stricmp(*args, "/new")) {

			if (create) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			create = TRUE;
		}

		//	Disk type options

		else if (_stricmp(*args, "/ram") == 0) {

			if (disk_type != VFD_DISKTYPE_FILE) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			disk_type = VFD_DISKTYPE_RAM;
		}

		//	Protect options
		else if (_stricmp(*args, "/p") == 0 ||
			_stricmp(*args, "/w") == 0) {

			if (protect) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			protect = (CHAR)toupper(*(*args + 1));
		}

		//	media size options

		else if (strcmp(*args, "/160") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F5_160;
		}
		else if (strcmp(*args, "/180") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F5_180;
		}
		else if (strcmp(*args, "/320") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F5_320;
		}
		else if (strcmp(*args, "/360") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F5_360;
		}
		else if (strcmp(*args, "/640") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F3_640;
		}
		else if (strcmp(*args, "/720") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F3_720;
		}
		else if (strcmp(*args, "/820") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F3_820;
		}
		else if (strcmp(*args, "/120") == 0 ||
			strcmp(*args, "/1.20") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F3_1P2;
		}
		else if (strcmp(*args, "/144") == 0 ||
			strcmp(*args, "/1.44") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F3_1P4;
		}
		else if (strcmp(*args, "/168") == 0 ||
			strcmp(*args, "/1.68") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F3_1P6;
		}
		else if (strcmp(*args, "/172") == 0 ||
			strcmp(*args, "/1.72") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F3_1P7;
		}
		else if (strcmp(*args, "/288") == 0 ||
			strcmp(*args, "/2.88") == 0) {
			if (media_type) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			media_type = VFD_MEDIA_F3_2P8;
		}

		//	5.25 inch media

		else if (strcmp(*args, "/5") == 0 ||
			strcmp(*args, "/525") == 0 ||
			strcmp(*args, "/5.25") == 0) {

			if (five_inch) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			five_inch = TRUE;
		}

		//	target option

		else if (isalnum(**args) &&
			*(*args + 1) == ':' &&
			*(*args + 2) == '\0') {

			if (target != TARGET_NONE) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			target = toupper(**args);
		}

		//	filename

		else if (**args != '/') {
			if (file_name) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			file_name = *args;
		}
		else {
			PrintMessage(MSG_UNKNOWN_OPTION, *args);
			PrintMessage(MSG_HINT_OPEN, help_progname);
			return VFD_NG;
		}

		args++;
	}

	if (target == TARGET_NONE) {
		// default target
		target = '0';
		PrintMessage(MSG_TARGET_NOTICE, target);
	}

	//	check target file

	if (file_name) {
		DWORD			file_attr;
		VFD_FILETYPE	file_type;
		ULONG			image_size;
		BOOL			overwrite = FALSE;

		ret = VfdCheckImageFile(
			file_name, &file_attr, &file_type, &image_size);

		if (ret == ERROR_FILE_NOT_FOUND) {
			
			//	the target file does not exist
			
			if (!create) {				// create option not specified

				if (mode == OPERATION_FORCE) {
					PrintMessage(MSG_CREATE_NOTICE);
				}
				else {
					printf("%s", SystemError(ret));

					if (mode == OPERATION_QUIT ||
						InputChar(MSG_CREATE_CONFIRM, "yn") == 'n') {
						return VFD_NG;
					}
				}

				create = TRUE;
			}
		}
		else if (ret == ERROR_SUCCESS) {
			
			//	the target file exists

			if (create) {				//	create option is specified

				if (mode == OPERATION_FORCE) {
					PrintMessage(MSG_OVERWRITE_NOTICE);
				}
				else {
					printf("%s", SystemError(ERROR_FILE_EXISTS));

					if (mode == OPERATION_QUIT ||
						InputChar(MSG_OVERWRITE_CONFIRM, "yn") == 'n') {
						return VFD_NG;
					}
				}

				overwrite = TRUE;
			}
		}
		else {
			PrintMessage(MSG_OPEN_NG, file_name);
			printf("%s", SystemError(ret));
			return VFD_NG;
		}

		//
		//	create or overwrite the target file
		//

		if (create) {

			if (media_type == VFD_MEDIA_NONE) {

				if (mode == OPERATION_FORCE) {
					PrintMessage(MSG_CREATE144_NOTICE);
				}
				else {
					PrintMessage(MSG_FILE_MEDIA_UNKNOWN);

					if (mode == OPERATION_QUIT ||
						InputChar(MSG_CREATE144_CONFIRM, "yn") == 'n') {
						return VFD_NG;
					}
				}

				media_type = VFD_MEDIA_F3_1P4;
			}

			ret = VfdCreateImageFile(
				file_name, media_type, VFD_FILETYPE_RAW, overwrite);

			if (ret != ERROR_SUCCESS) {
				PrintMessage(MSG_CREATE_NG, file_name);
				printf("%s", SystemError(ret));
				return VFD_NG;
			}

			PrintMessage(MSG_FILE_CREATED);

			ret = VfdCheckImageFile(
				file_name, &file_attr, &file_type, &image_size);

			if (ret != ERROR_SUCCESS) {
				PrintMessage(MSG_OPEN_NG, file_name);
				printf("%s", SystemError(ret));
				return VFD_NG;
			}
		}
		else {
			//
			//	use the existing target file
			//	check image size and the media type
			//

			VFD_MEDIA	def_media;	//	default media for image size
			ULONG		media_size;	//	specified media size

			media_size	= VfdGetMediaSize(media_type);

			if (media_size > image_size) {

				//	specified media is too large for the image

				PrintMessage(MSG_IMAGE_TOO_SMALL);
				return VFD_NG;
			}

			def_media	= VfdLookupMedia(image_size);

			if (def_media == VFD_MEDIA_NONE) {

				//	image is too small for the smallest media

				PrintMessage(MSG_IMAGE_TOO_SMALL);
				return VFD_NG;
			}

			if (media_type == VFD_MEDIA_NONE) {

				//	media type is not specified

				ULONG def_size = VfdGetMediaSize(def_media);

				if (def_size != image_size) {

					//	image size does not match the largest media size

					PrintMessage(MSG_NO_MATCHING_MEDIA, image_size);

					if (mode == OPERATION_FORCE) {
						PrintMessage(MSG_MEDIATYPE_NOTICE, 
							VfdMediaTypeName(def_media), def_size);
					}
					else if (mode == OPERATION_QUIT) {
						return VFD_NG;
					}
					else {
						PrintMessage(MSG_MEDIATYPE_SUGGEST,
							VfdMediaTypeName(def_media), def_size);

						if (InputChar(MSG_MEDIATYPE_CONFIRM, "yn") == 'n') {
							return VFD_NG;
						}
					}
				}

				media_type = def_media;
			}
		}

		//	check file attributes against the disk type

		if (file_type == VFD_FILETYPE_ZIP ||
			(file_attr & (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_COMPRESSED | FILE_ATTRIBUTE_ENCRYPTED))) {

			if (disk_type != VFD_DISKTYPE_RAM) {

				if (mode == OPERATION_FORCE) {
					PrintMessage(MSG_RAM_MODE_NOTICE);
				}
				else {
					PrintMessage(MSG_RAM_MODE_ONLY);

					if (mode == OPERATION_QUIT ||
						InputChar(MSG_RAM_MODE_CONFIRM, "yn") == 'n') {
						return VFD_NG;
					}
				}

				disk_type = VFD_DISKTYPE_RAM;
			}
		}

		if (disk_type != VFD_DISKTYPE_FILE) {
			if (!protect) {
				PrintMessage(MSG_DEFAULT_PROTECT);
				protect = 'P';
			}
		}
	}
	else {
		//
		//	pure RAM disk
		//
		disk_type = VFD_DISKTYPE_RAM;

		if (media_type == VFD_MEDIA_NONE) {

			if (mode == OPERATION_FORCE) {
				PrintMessage(MSG_CREATE144_NOTICE);
			}
			else {
				PrintMessage(MSG_RAM_MEDIA_UNKNOWN);

				if (mode == OPERATION_QUIT ||
					InputChar(MSG_CREATE144_CONFIRM, "yn") == 'n') {
					return VFD_NG;
				}
			}

			media_type = VFD_MEDIA_F3_1P4;
		}
	}

	if (protect == 'P') {
		media_flags |= VFD_FLAG_WRITE_PROTECTED;
	}

	if (five_inch &&
		VfdGetMediaSize(media_type) ==
		VfdGetMediaSize((VFD_MEDIA)(media_type + 1))) {
		media_type = (VFD_MEDIA)(media_type + 1);
	}

	//	ensure that the driver is installed

	if (driver_state == VFD_NOT_INSTALLED &&
		Install(NULL) != VFD_OK) {
		return VFD_NG;
	}

	//	ensure that the driver is up to date

	if (CheckDriver() != VFD_OK) {
		return VFD_NG;
	}

	//	ensure that the driver is running

	if (driver_state != SERVICE_RUNNING &&
		Start(NULL) != VFD_OK) {
		return VFD_NG;
	}

	//	Open the target device

	hDevice = VfdOpenDevice(target);

	if (hDevice == INVALID_HANDLE_VALUE) {
		ret = GetLastError();
		PrintMessage(MSG_ACCESS_NG, target);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	//	Ensure that the drive is empty

	ret = VfdGetMediaState(hDevice);

	if (ret != ERROR_NOT_READY) {
		if (ret == ERROR_SUCCESS ||
			ret == ERROR_WRITE_PROTECT) {
			PrintMessage(MSG_DRIVE_BUSY);
		}
		else {
			PrintMessage(MSG_GET_MEDIA_NG);
			printf("%s", SystemError(ret));
		}

		CloseHandle(hDevice);
		return VFD_NG;
	}

	//	Open the image file

	ret = VfdOpenImage(hDevice, file_name,
		disk_type, media_type, media_flags);

	if (ret != ERROR_SUCCESS) {
		PrintMessage(MSG_OPEN_NG, file_name ? file_name : "<RAM>");
		printf("%s", SystemError(ret));

		CloseHandle(hDevice);
		return VFD_NG;
	}

	//	assign a drive letter if the drive has none

	VfdGetGlobalLink(hDevice, &letter);

	if (!isalpha(letter)) {
		VfdGetLocalLink(hDevice, &letter);
	}

	if (!isalpha(letter)) {
		VfdSetLocalLink(hDevice, VfdChooseLetter());
	}

	//	Get the actually opened image information.

	PrintImageInfo(hDevice);

	CloseHandle(hDevice);

	return VFD_OK;
}