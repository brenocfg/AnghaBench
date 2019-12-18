#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/  AssociatedEndpoint; } ;
typedef  TYPE_1__* PTDI_BUCKET ;
typedef  int /*<<< orphan*/  PCONNECTION_ENDPOINT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BucketCompletionWorker (TYPE_1__*) ; 
 int /*<<< orphan*/  ChewCreate (int /*<<< orphan*/  (*) (TYPE_1__*),TYPE_1__*) ; 
 int /*<<< orphan*/  ReferenceObject (int /*<<< orphan*/ ) ; 

VOID
CompleteBucket(PCONNECTION_ENDPOINT Connection, PTDI_BUCKET Bucket, const BOOLEAN Synchronous)
{
    ReferenceObject(Connection);
    Bucket->AssociatedEndpoint = Connection;
    if (Synchronous)
    {
        BucketCompletionWorker(Bucket);
    }
    else
    {
        ChewCreate(BucketCompletionWorker, Bucket);
    }
}