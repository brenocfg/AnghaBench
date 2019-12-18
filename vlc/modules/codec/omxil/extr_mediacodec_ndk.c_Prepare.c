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
struct TYPE_3__ {int /*<<< orphan*/  i_quirks; int /*<<< orphan*/  psz_name; int /*<<< orphan*/  i_codec; int /*<<< orphan*/  i_cat; int /*<<< orphan*/  psz_mime; int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_1__ mc_api ;

/* Variables and functions */
 int MC_API_ERROR ; 
 int /*<<< orphan*/  MC_API_VIDEO_QUIRKS_SUPPORT_INTERLACED ; 
 int /*<<< orphan*/  MediaCodec_GetName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMXCodec_GetQuirks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Prepare(mc_api * api, int i_profile)
{
    free(api->psz_name);

    api->i_quirks = 0;
    api->psz_name = MediaCodec_GetName(api->p_obj, api->psz_mime,
                                       i_profile, &api->i_quirks);
    if (!api->psz_name)
        return MC_API_ERROR;
    api->i_quirks |= OMXCodec_GetQuirks(api->i_cat, api->i_codec, api->psz_name,
                                        strlen(api->psz_name));
    /* Allow interlaced picture after API 21 */
    api->i_quirks |= MC_API_VIDEO_QUIRKS_SUPPORT_INTERLACED;
    return 0;
}