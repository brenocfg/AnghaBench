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
typedef  int /*<<< orphan*/  vtype_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VBLK ; 
 int /*<<< orphan*/  VCHR ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VFIFO ; 
 int /*<<< orphan*/  VLNK ; 
 int /*<<< orphan*/  VNON ; 
 int /*<<< orphan*/  VREG ; 
 int /*<<< orphan*/  VSOCK ; 

vtype_t
vn_mode_to_vtype(mode_t mode)
{
	if (S_ISREG(mode))
		return (VREG);

	if (S_ISDIR(mode))
		return (VDIR);

	if (S_ISCHR(mode))
		return (VCHR);

	if (S_ISBLK(mode))
		return (VBLK);

	if (S_ISFIFO(mode))
		return (VFIFO);

	if (S_ISLNK(mode))
		return (VLNK);

	if (S_ISSOCK(mode))
		return (VSOCK);

	return (VNON);
}