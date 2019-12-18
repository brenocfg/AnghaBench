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
struct block_device {int /*<<< orphan*/  bd_dev; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 unsigned int MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 struct block_device* vdev_lookup_bdev (char const*) ; 
 unsigned int zvol_major ; 

__attribute__((used)) static boolean_t
zvol_is_zvol_impl(const char *device)
{
	struct block_device *bdev;
	unsigned int major;

	bdev = vdev_lookup_bdev(device);
	if (IS_ERR(bdev))
		return (B_FALSE);

	major = MAJOR(bdev->bd_dev);
	bdput(bdev);

	if (major == zvol_major)
		return (B_TRUE);

	return (B_FALSE);
}