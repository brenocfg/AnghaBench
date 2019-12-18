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
struct jpeg_decompress_struct {int /*<<< orphan*/  client_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ fz_dctd ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int custmptr ; 
 int /*<<< orphan*/  fz_dct_mem_alloc ; 
 int /*<<< orphan*/  fz_dct_mem_free ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_malloc_struct (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int jpeg_cust_mem_data ; 
 int /*<<< orphan*/  jpeg_cust_mem_init (int,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fz_dct_mem_init(struct jpeg_decompress_struct *cinfo, fz_dctd *state)
{
	jpeg_cust_mem_data *custmptr;
	custmptr = fz_malloc_struct(state->ctx, jpeg_cust_mem_data);
	if (!jpeg_cust_mem_init(custmptr, (void *) state, NULL, NULL, NULL,
				fz_dct_mem_alloc, fz_dct_mem_free,
				fz_dct_mem_alloc, fz_dct_mem_free, NULL))
	{
		fz_free(state->ctx, custmptr);
		fz_throw(state->ctx, FZ_ERROR_GENERIC, "cannot initialize custom JPEG memory handler");
	}
	cinfo->client_data = custmptr;
}