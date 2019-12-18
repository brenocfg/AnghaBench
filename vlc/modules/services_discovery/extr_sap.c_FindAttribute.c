#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  i_attributes; int /*<<< orphan*/  pp_attributes; TYPE_1__* mediav; } ;
typedef  TYPE_2__ sdp_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_attributes; int /*<<< orphan*/  pp_attributes; } ;

/* Variables and functions */
 char* GetAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const char *FindAttribute (const sdp_t *sdp, unsigned media,
                                  const char *name)
{
    /* Look for media attribute, and fallback to session */
    const char *attr = GetAttribute (sdp->mediav[media].pp_attributes,
                                     sdp->mediav[media].i_attributes, name);
    if (attr == NULL)
        attr = GetAttribute (sdp->pp_attributes, sdp->i_attributes, name);
    return attr;
}