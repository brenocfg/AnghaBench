#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  DefaultDacl; } ;
typedef  TYPE_1__ TOKEN_USER ;
typedef  TYPE_1__ TOKEN_PRIVILEGES ;
typedef  TYPE_1__ TOKEN_PRIMARY_GROUP ;
typedef  TYPE_1__ TOKEN_OWNER ;
typedef  TYPE_1__ TOKEN_GROUPS ;
typedef  TYPE_1__ TOKEN_DEFAULT_DACL ;
typedef  TYPE_1__* PTOKEN_USER ;
typedef  TYPE_1__* PTOKEN_PRIVILEGES ;
typedef  TYPE_1__* PTOKEN_PRIMARY_GROUP ;
typedef  TYPE_1__* PTOKEN_OWNER ;
typedef  TYPE_1__* PTOKEN_GROUPS ;
typedef  TYPE_1__* PTOKEN_DEFAULT_DACL ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DisplayDacl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisplayTokenSids (TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetFromToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TokenDefaultDacl ; 
 int /*<<< orphan*/  TokenGroups ; 
 int /*<<< orphan*/  TokenOwner ; 
 int /*<<< orphan*/  TokenPrimaryGroup ; 
 int /*<<< orphan*/  TokenPrivileges ; 
 int /*<<< orphan*/  TokenUser ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
DisplayToken(HANDLE hTokenSource)
{
	TOKEN_USER*			 pTokenUser         = (PTOKEN_USER)			 GetFromToken(hTokenSource, TokenUser);
	TOKEN_GROUPS*		 pTokenGroups		= (PTOKEN_GROUPS)		 GetFromToken(hTokenSource, TokenGroups);
	TOKEN_OWNER*		 pTokenOwner		= (PTOKEN_OWNER)		 GetFromToken(hTokenSource, TokenOwner);
	TOKEN_PRIMARY_GROUP* pTokenPrimaryGroup = (PTOKEN_PRIMARY_GROUP) GetFromToken(hTokenSource, TokenPrimaryGroup);
	TOKEN_PRIVILEGES*	 pTokenPrivileges	= (PTOKEN_PRIVILEGES)	 GetFromToken(hTokenSource, TokenPrivileges);
	TOKEN_DEFAULT_DACL*	 pTokenDefaultDacl	= (PTOKEN_DEFAULT_DACL)	 GetFromToken(hTokenSource, TokenDefaultDacl);

	DisplayTokenSids(pTokenUser, pTokenGroups, pTokenOwner, pTokenPrimaryGroup);
	// DisplayTokenPrivileges(pTokenPrivileges);
	DisplayDacl(pTokenDefaultDacl->DefaultDacl);

	free(pTokenUser);
	free(pTokenGroups);
	free(pTokenOwner);
	free(pTokenPrimaryGroup);
	free(pTokenPrivileges);
	free(pTokenDefaultDacl);
}