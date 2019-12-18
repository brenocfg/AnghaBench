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
typedef  TYPE_1__* nvlist_prtctl_t ;
typedef  enum nvlist_prtctl_fmt { ____Placeholder_nvlist_prtctl_fmt } nvlist_prtctl_fmt ;
struct TYPE_3__ {char const* nvprt_nmfmt; char const* nvprt_eomfmt; char* nvprt_btwnarrfmt; int /*<<< orphan*/  nvprt_btwnarrfmt_nl; } ;

/* Variables and functions */
#define  NVLIST_FMT_BTWN_ARRAY 130 
#define  NVLIST_FMT_MEMBER_NAME 129 
#define  NVLIST_FMT_MEMBER_POSTAMBLE 128 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

void
nvlist_prtctl_setfmt(nvlist_prtctl_t pctl, enum nvlist_prtctl_fmt which,
    const char *fmt)
{
	switch (which) {
	case NVLIST_FMT_MEMBER_NAME:
		if (fmt == NULL)
			fmt = "%s = ";
		pctl->nvprt_nmfmt = fmt;
		break;

	case NVLIST_FMT_MEMBER_POSTAMBLE:
		if (fmt == NULL)
			fmt = "\n";
		pctl->nvprt_eomfmt = fmt;
		break;

	case NVLIST_FMT_BTWN_ARRAY:
		if (fmt == NULL) {
			pctl->nvprt_btwnarrfmt = " ";
			pctl->nvprt_btwnarrfmt_nl = 0;
		} else {
			pctl->nvprt_btwnarrfmt = fmt;
			pctl->nvprt_btwnarrfmt_nl = (strstr(fmt, "\n") != NULL);
		}
		break;

	default:
		break;
	}
}