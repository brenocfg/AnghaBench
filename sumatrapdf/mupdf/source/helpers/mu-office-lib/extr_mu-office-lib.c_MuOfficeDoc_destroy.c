#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* path; int /*<<< orphan*/  ctx; int /*<<< orphan*/  doc; int /*<<< orphan*/  password_sem; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ MuOfficeDoc ;

/* Variables and functions */
 int /*<<< orphan*/  MuOfficeDoc_abortLoad (TYPE_1__*) ; 
 int /*<<< orphan*/  Pal_Mem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_document (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mu_destroy_semaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mu_destroy_thread (int /*<<< orphan*/ *) ; 

void MuOfficeDoc_destroy(MuOfficeDoc *doc)
{
	MuOfficeDoc_abortLoad(doc);
	mu_destroy_thread(&doc->thread);
	mu_destroy_semaphore(&doc->password_sem);

	fz_drop_document(doc->ctx, doc->doc);
	fz_drop_context(doc->ctx);
	Pal_Mem_free(doc->path);
	Pal_Mem_free(doc);
}