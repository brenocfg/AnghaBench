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
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_dirname (char*,char const*,int) ; 
 int /*<<< orphan*/  fz_read_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * htdoc_open_document_with_buffer (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_document *
htdoc_open_document(fz_context *ctx, const char *filename)
{
	char dirname[2048];
	fz_dirname(dirname, filename, sizeof dirname);
	return htdoc_open_document_with_buffer(ctx, dirname, fz_read_file(ctx, filename));
}