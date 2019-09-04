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
struct comclassredirect_data {int miscmask; scalar_t__ miscstatusdocprint; scalar_t__ miscstatusthumbnail; scalar_t__ miscstatuscontent; scalar_t__ miscstatusicon; scalar_t__ miscstatus; } ;
typedef  enum comclass_miscfields { ____Placeholder_comclass_miscfields } comclass_miscfields ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int cbSize; scalar_t__ lpData; } ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ACTCTX_SECTION_KEYED_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FindActCtxSectionGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*) ; 
#define  MiscStatus 132 
#define  MiscStatusContent 131 
#define  MiscStatusDocPrint 130 
#define  MiscStatusIcon 129 
#define  MiscStatusThumbnail 128 
 int /*<<< orphan*/  TRUE ; 
 int dvaspect_to_miscfields (scalar_t__) ; 

BOOL actctx_get_miscstatus(const CLSID *clsid, DWORD aspect, DWORD *status)
{
    ACTCTX_SECTION_KEYED_DATA data;

    data.cbSize = sizeof(data);
    if (FindActCtxSectionGuid(0, NULL, ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION,
                              clsid, &data))
    {
        struct comclassredirect_data *comclass = (struct comclassredirect_data*)data.lpData;
        enum comclass_miscfields misc = dvaspect_to_miscfields(aspect);

        if (!(comclass->miscmask & misc))
        {
            if (!(comclass->miscmask & MiscStatus))
            {
                *status = 0;
                return TRUE;
            }
            misc = MiscStatus;
        }

        switch (misc)
        {
        case MiscStatus:
            *status = comclass->miscstatus;
            break;
        case MiscStatusIcon:
            *status = comclass->miscstatusicon;
            break;
        case MiscStatusContent:
            *status = comclass->miscstatuscontent;
            break;
        case MiscStatusThumbnail:
            *status = comclass->miscstatusthumbnail;
            break;
        case MiscStatusDocPrint:
            *status = comclass->miscstatusdocprint;
            break;
        default:
           ;
        };

        return TRUE;
    }
    else
        return FALSE;
}