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
struct vmx {int /*<<< orphan*/ * apic_page; int /*<<< orphan*/  vm; } ;
struct vlapic_vtx {struct vmx* vmx; } ;
struct vlapic {int vcpuid; struct LAPIC* apic_page; int /*<<< orphan*/  vm; } ;
struct LAPIC {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct vlapic*) ; 
 int /*<<< orphan*/  bzero (struct vlapic*,int) ; 
 struct vlapic* malloc (int) ; 
 int /*<<< orphan*/  vlapic_init (struct vlapic*) ; 

__attribute__((used)) static struct vlapic *
vmx_vlapic_init(void *arg, int vcpuid)
{
	struct vmx *vmx;
	struct vlapic *vlapic;
	struct vlapic_vtx *vlapic_vtx;
	
	vmx = arg;

	vlapic = malloc(sizeof(struct vlapic_vtx));
	assert(vlapic);
	bzero(vlapic, sizeof(struct vlapic));
	vlapic->vm = vmx->vm;
	vlapic->vcpuid = vcpuid;
	vlapic->apic_page = (struct LAPIC *)&vmx->apic_page[vcpuid];

	vlapic_vtx = (struct vlapic_vtx *)vlapic;
	vlapic_vtx->vmx = vmx;

	vlapic_init(vlapic);

	return (vlapic);
}