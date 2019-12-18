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
typedef  scalar_t__ vtype_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFIFO ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  S_IFSOCK ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 scalar_t__ VDIR ; 
 scalar_t__ VFIFO ; 
 scalar_t__ VLNK ; 
 int /*<<< orphan*/  VNON ; 
 scalar_t__ VREG ; 
 scalar_t__ VSOCK ; 

mode_t
vn_vtype_to_mode(vtype_t vtype)
{
	if (vtype == VREG)
		return (S_IFREG);

	if (vtype == VDIR)
		return (S_IFDIR);

	if (vtype == VCHR)
		return (S_IFCHR);

	if (vtype == VBLK)
		return (S_IFBLK);

	if (vtype == VFIFO)
		return (S_IFIFO);

	if (vtype == VLNK)
		return (S_IFLNK);

	if (vtype == VSOCK)
		return (S_IFSOCK);

	return (VNON);
}