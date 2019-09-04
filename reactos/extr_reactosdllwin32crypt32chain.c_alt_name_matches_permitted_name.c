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
struct TYPE_5__ {size_t cPermittedSubtree; TYPE_1__* rgPermittedSubtree; } ;
struct TYPE_4__ {int /*<<< orphan*/  Base; } ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CERT_NAME_CONSTRAINTS_INFO ;
typedef  int /*<<< orphan*/  CERT_ALT_NAME_ENTRY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ alt_name_matches (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t*,scalar_t__*) ; 

__attribute__((used)) static BOOL alt_name_matches_permitted_name(const CERT_ALT_NAME_ENTRY *name,
 const CERT_NAME_CONSTRAINTS_INFO *nameConstraints, DWORD *trustErrorStatus,
 BOOL *present)
{
    DWORD i;
    BOOL match = FALSE;

    for (i = 0; !match && i < nameConstraints->cPermittedSubtree; i++)
        match = alt_name_matches(name,
         &nameConstraints->rgPermittedSubtree[i].Base, trustErrorStatus,
         present);
    return match;
}