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
struct background_worker_config {int dummy; } ;
struct background_worker {int dummy; } ;

/* Variables and functions */
 struct background_worker* background_worker_Create (void*,struct background_worker_config*) ; 

struct background_worker* background_worker_New( void* owner,
    struct background_worker_config* conf )
{
    return background_worker_Create(owner, conf);
}