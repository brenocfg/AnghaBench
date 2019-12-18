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
typedef  TYPE_1__* j_common_ptr ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int /*<<< orphan*/  client_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int custmptr ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_jpg_mem_alloc ; 
 int /*<<< orphan*/  fz_jpg_mem_free ; 
 int /*<<< orphan*/  fz_malloc_struct (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int jpeg_cust_mem_data ; 
 int /*<<< orphan*/  jpeg_cust_mem_init (int,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fz_jpg_mem_init(j_common_ptr cinfo, fz_context *ctx)
{
	jpeg_cust_mem_data *custmptr;
	custmptr = fz_malloc_struct(ctx, jpeg_cust_mem_data);
	if (!jpeg_cust_mem_init(custmptr, (void *) ctx, NULL, NULL, NULL,
				fz_jpg_mem_alloc, fz_jpg_mem_free,
				fz_jpg_mem_alloc, fz_jpg_mem_free, NULL))
	{
		fz_free(ctx, custmptr);
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot initialize custom JPEG memory handler");
	}
	cinfo->client_data = custmptr;
}