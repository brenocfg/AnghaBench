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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int packed; int cmd_len; int coord_len; } ;
typedef  TYPE_1__ fz_path ;
struct TYPE_5__ {int coord_len; int cmd_len; } ;
typedef  TYPE_2__ fz_packed_path ;

/* Variables and functions */
#define  FZ_PATH_PACKED_FLAT 130 
#define  FZ_PATH_PACKED_OPEN 129 
#define  FZ_PATH_UNPACKED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int fz_packed_path_size(const fz_path *path)
{
	switch (path->packed)
	{
	case FZ_PATH_UNPACKED:
		if (path->cmd_len > 255 || path->coord_len > 255)
			return sizeof(fz_path);
		return sizeof(fz_packed_path) + sizeof(float) * path->coord_len + sizeof(uint8_t) * path->cmd_len;
	case FZ_PATH_PACKED_OPEN:
		return sizeof(fz_path);
	case FZ_PATH_PACKED_FLAT:
	{
		fz_packed_path *pack = (fz_packed_path *)path;
		return sizeof(fz_packed_path) + sizeof(float) * pack->coord_len + sizeof(uint8_t) * pack->cmd_len;
	}
	default:
		assert("This never happens" == NULL);
		return 0;
	}
}