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
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 scalar_t__ OneTrivialLab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsCreateLab2Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckFloatLabTransforms(void)
{
    return OneTrivialLab(cmsCreateLab4Profile(DbgThread(), NULL), cmsCreateLab4Profile(DbgThread(), NULL),  "Lab4/Lab4") &&
           OneTrivialLab(cmsCreateLab2Profile(DbgThread(), NULL), cmsCreateLab2Profile(DbgThread(), NULL),  "Lab2/Lab2") &&
           OneTrivialLab(cmsCreateLab4Profile(DbgThread(), NULL), cmsCreateLab2Profile(DbgThread(), NULL),  "Lab4/Lab2") &&
           OneTrivialLab(cmsCreateLab2Profile(DbgThread(), NULL), cmsCreateLab4Profile(DbgThread(), NULL),  "Lab2/Lab4");
}