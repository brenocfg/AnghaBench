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
struct TYPE_3__ {char* fBuffer; char* cBuffer; int /*<<< orphan*/  cctx; } ;
typedef  TYPE_1__ resources ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void freeResources(resources ress, char *outFilename)
{
    free(ress.fBuffer);
    free(ress.cBuffer);
    ZSTD_freeCCtx(ress.cctx);   /* never fails */
    free(outFilename);
}