#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct assembly_version {int /*<<< orphan*/  revision; int /*<<< orphan*/  build; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct actctx_loader {unsigned int num_dependencies; TYPE_1__* dependencies; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; struct assembly_version version; int /*<<< orphan*/  delayed; int /*<<< orphan*/  optional; } ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ STATUS_SXS_CANT_GEN_ACTCTX ; 
 scalar_t__ lookup_assembly (struct actctx_loader*,TYPE_1__*) ; 

__attribute__((used)) static NTSTATUS parse_depend_manifests(struct actctx_loader* acl)
{
    NTSTATUS status = STATUS_SUCCESS;
    unsigned int i;

    for (i = 0; i < acl->num_dependencies; i++)
    {
        if (lookup_assembly(acl, &acl->dependencies[i]) != STATUS_SUCCESS)
        {
            if (!acl->dependencies[i].optional && !acl->dependencies[i].delayed)
            {
                const struct assembly_version *ver = &acl->dependencies[i].version;
                DPRINT1( "Could not find dependent assembly %S (%u.%u.%u.%u)\n",
                    acl->dependencies[i].name,
                    ver->major, ver->minor, ver->build, ver->revision );
                status = STATUS_SXS_CANT_GEN_ACTCTX;
                break;
            }
        }
    }
    /* FIXME should now iterate through all refs */
    return status;
}