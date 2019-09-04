#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t GroupCount; int /*<<< orphan*/ * Groups; } ;
struct TYPE_5__ {int /*<<< orphan*/  User; } ;
typedef  TYPE_1__ TOKEN_USER ;
typedef  int /*<<< orphan*/  TOKEN_PRIMARY_GROUP ;
typedef  int /*<<< orphan*/  TOKEN_OWNER ;
typedef  TYPE_2__ TOKEN_GROUPS ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PrintSid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
DisplayTokenSids(TOKEN_USER* pUser,
				 TOKEN_GROUPS* pGroups,
				 TOKEN_OWNER* pOwner,
				 TOKEN_PRIMARY_GROUP* pPrimary)
{
	DWORD i;

	printf("\nSids:\n");
	PrintSid(&pUser->User, pOwner, pPrimary);
	printf("\nGroups:\n");
	for (i = 0; i < pGroups->GroupCount; i++)
		PrintSid(&pGroups->Groups[i], pOwner, pPrimary);
}