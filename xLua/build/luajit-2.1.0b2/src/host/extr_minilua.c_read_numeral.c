#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char current; int /*<<< orphan*/  buff; int /*<<< orphan*/  decpoint; } ;
struct TYPE_10__ {int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_NUMBER ; 
 int /*<<< orphan*/  buffreplace (TYPE_2__*,char,int /*<<< orphan*/ ) ; 
 scalar_t__ check_next (TYPE_2__*,char*) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  luaO_str2d (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_lexerror (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save (TYPE_2__*,char) ; 
 int /*<<< orphan*/  save_and_next (TYPE_2__*) ; 

__attribute__((used)) static void read_numeral(LexState*ls,SemInfo*seminfo){
do{
save_and_next(ls);
}while(isdigit(ls->current)||ls->current=='.');
if(check_next(ls,"Ee"))
check_next(ls,"+-");
while(isalnum(ls->current)||ls->current=='_')
save_and_next(ls);
save(ls,'\0');
buffreplace(ls,'.',ls->decpoint);
if(!luaO_str2d(luaZ_buffer(ls->buff),&seminfo->r))
luaX_lexerror(ls,"malformed number",TK_NUMBER);
}