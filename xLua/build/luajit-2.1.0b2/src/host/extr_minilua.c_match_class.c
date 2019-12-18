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

/* Variables and functions */
 int isalnum (int) ; 
 int isalpha (int) ; 
 int iscntrl (int) ; 
 int isdigit (int) ; 
 int islower (int) ; 
 int ispunct (int) ; 
 int isspace (int) ; 
 int isupper (int) ; 
 int isxdigit (int) ; 
 int tolower (int) ; 

__attribute__((used)) static int match_class(int c,int cl){
int res;
switch(tolower(cl)){
case'a':res=isalpha(c);break;
case'c':res=iscntrl(c);break;
case'd':res=isdigit(c);break;
case'l':res=islower(c);break;
case'p':res=ispunct(c);break;
case's':res=isspace(c);break;
case'u':res=isupper(c);break;
case'w':res=isalnum(c);break;
case'x':res=isxdigit(c);break;
case'z':res=(c==0);break;
default:return(cl==c);
}
return(islower(cl)?res:!res);
}