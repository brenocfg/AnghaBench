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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  RequestContext; scalar_t__ RequestNotifyObject; } ;
struct TYPE_5__ {int /*<<< orphan*/  AssociatedEndpoint; int /*<<< orphan*/  Information; int /*<<< orphan*/  Status; TYPE_1__ Request; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PTDI_BUCKET ;
typedef  int /*<<< orphan*/  (* PTCP_COMPLETION_ROUTINE ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  DereferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  TdiBucketLookasideList ; 

__attribute__((used)) static
VOID
BucketCompletionWorker(PVOID Context)
{
    PTDI_BUCKET Bucket = (PTDI_BUCKET)Context;
    PTCP_COMPLETION_ROUTINE Complete;
    
    Complete = (PTCP_COMPLETION_ROUTINE)Bucket->Request.RequestNotifyObject;
    
    Complete(Bucket->Request.RequestContext, Bucket->Status, Bucket->Information);
    
    DereferenceObject(Bucket->AssociatedEndpoint);

    ExFreeToNPagedLookasideList(&TdiBucketLookasideList, Bucket);
}