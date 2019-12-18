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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
#define  UU_ERROR_CALLBACK_FAILED 140 
#define  UU_ERROR_EMPTY 139 
#define  UU_ERROR_INVALID_ARGUMENT 138 
#define  UU_ERROR_INVALID_CHAR 137 
#define  UU_ERROR_INVALID_DIGIT 136 
#define  UU_ERROR_NONE 135 
#define  UU_ERROR_NOT_SUPPORTED 134 
#define  UU_ERROR_NO_MEMORY 133 
#define  UU_ERROR_OVERFLOW 132 
#define  UU_ERROR_SYSTEM 131 
#define  UU_ERROR_UNDERFLOW 130 
#define  UU_ERROR_UNKNOWN 129 
#define  UU_ERROR_UNKNOWN_FLAG 128 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 

const char *
uu_strerror(uint32_t code)
{
	const char *str;

	switch (code) {
	case UU_ERROR_NONE:
		str = dgettext(TEXT_DOMAIN, "No error");
		break;

	case UU_ERROR_INVALID_ARGUMENT:
		str = dgettext(TEXT_DOMAIN, "Invalid argument");
		break;

	case UU_ERROR_UNKNOWN_FLAG:
		str = dgettext(TEXT_DOMAIN, "Unknown flag passed");
		break;

	case UU_ERROR_NO_MEMORY:
		str = dgettext(TEXT_DOMAIN, "Out of memory");
		break;

	case UU_ERROR_CALLBACK_FAILED:
		str = dgettext(TEXT_DOMAIN, "Callback-initiated failure");
		break;

	case UU_ERROR_NOT_SUPPORTED:
		str = dgettext(TEXT_DOMAIN, "Operation not supported");
		break;

	case UU_ERROR_EMPTY:
		str = dgettext(TEXT_DOMAIN, "No value provided");
		break;

	case UU_ERROR_UNDERFLOW:
		str = dgettext(TEXT_DOMAIN, "Value too small");
		break;

	case UU_ERROR_OVERFLOW:
		str = dgettext(TEXT_DOMAIN, "Value too large");
		break;

	case UU_ERROR_INVALID_CHAR:
		str = dgettext(TEXT_DOMAIN,
		    "Value contains unexpected character");
		break;

	case UU_ERROR_INVALID_DIGIT:
		str = dgettext(TEXT_DOMAIN,
		    "Value contains digit not in base");
		break;

	case UU_ERROR_SYSTEM:
		str = dgettext(TEXT_DOMAIN, "Underlying system error");
		break;

	case UU_ERROR_UNKNOWN:
		str = dgettext(TEXT_DOMAIN, "Error status not known");
		break;

	default:
		errno = ESRCH;
		str = NULL;
		break;
	}
	return (str);
}