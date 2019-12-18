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
struct TYPE_4__ {void* Z; void* Y; void* X; } ;
struct TYPE_5__ {int version; int renderingIntent; int /*<<< orphan*/  reserved; scalar_t__ creator; TYPE_1__ illuminant; scalar_t__* attributes; scalar_t__ model; scalar_t__ manufacturer; scalar_t__ flags; int /*<<< orphan*/  platform; int /*<<< orphan*/  magic; int /*<<< orphan*/  date; scalar_t__ cmmId; } ;
typedef  TYPE_2__ icHeader ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* double2XYZtype (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  icMagicNumber ; 
 int /*<<< orphan*/  icSigMacintosh ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setdatetime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
setheader_common(fz_context *ctx, icHeader *header)
{
	header->cmmId = 0;
	header->version = 0x02200000;
	setdatetime(ctx, &(header->date));
	header->magic = icMagicNumber;
	header->platform = icSigMacintosh;
	header->flags = 0;
	header->manufacturer = 0;
	header->model = 0;
	header->attributes[0] = 0;
	header->attributes[1] = 0;
	header->renderingIntent = 3;
	header->illuminant.X = double2XYZtype(ctx, (float) 0.9642);
	header->illuminant.Y = double2XYZtype(ctx, (float) 1.0);
	header->illuminant.Z = double2XYZtype(ctx, (float) 0.8249);
	header->creator = 0;
	memset(header->reserved, 0, 44);
}