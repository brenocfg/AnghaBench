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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* pdf_sprint_encrypted_obj (int /*<<< orphan*/ *,char*,int,int*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
pdf_sprint_obj(fz_context *ctx, char *buf, int cap, int *len, pdf_obj *obj, int tight, int ascii)
{
	return pdf_sprint_encrypted_obj(ctx, buf, cap, len, obj, tight, ascii, NULL, 0, 0);
}