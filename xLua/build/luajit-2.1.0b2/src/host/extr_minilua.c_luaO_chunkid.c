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
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strcspn (char const*,char*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static void luaO_chunkid(char*out,const char*source,size_t bufflen){
if(*source=='='){
strncpy(out,source+1,bufflen);
out[bufflen-1]='\0';
}
else{
if(*source=='@'){
size_t l;
source++;
bufflen-=sizeof(" '...' ");
l=strlen(source);
strcpy(out,"");
if(l>bufflen){
source+=(l-bufflen);
strcat(out,"...");
}
strcat(out,source);
}
else{
size_t len=strcspn(source,"\n\r");
bufflen-=sizeof(" [string \"...\"] ");
if(len>bufflen)len=bufflen;
strcpy(out,"[string \"");
if(source[len]!='\0'){
strncat(out,source,len);
strcat(out,"...");
}
else
strcat(out,source);
strcat(out,"\"]");
}
}
}