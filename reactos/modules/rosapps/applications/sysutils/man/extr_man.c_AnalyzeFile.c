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
 int /*<<< orphan*/  BOLD ; 
 int /*<<< orphan*/  ITALIC ; 
 int MAXLINE ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  SetCl (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  manfile ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  sh_outp (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  text_outp (char*) ; 
 int /*<<< orphan*/  th_outp (char*,char*) ; 

int
AnalyzeFile()
{
    char *cur_string=(char*)malloc(sizeof(char)*MAXLINE);
    char *THtag=(char*)malloc(sizeof(char)*MAXLINE);




    while(fgets(cur_string,MAXLINE,manfile))

/* TAGs processing */
     if((cur_string[0]=='.')&&(cur_string[1]=='S')&&
       (cur_string[2]=='H')) // .SH tag
      {
       SetCl(BOLD);
       sh_outp(cur_string);
       SetCl(NORMAL);
      }
     else
     if((cur_string[0]=='.')&&(cur_string[1]=='I')&&
       (cur_string[2]==' ')) // .I tag
      {
       SetCl(ITALIC);
       text_outp(cur_string);
       SetCl(NORMAL);
      }
     else
     if((cur_string[0]=='.')&&(cur_string[1]=='/')&&
       (cur_string[2]=='\"')); // ./" tag (comment)

     else
     if((cur_string[0]=='.')&&(cur_string[1]=='T')&&
       (cur_string[2]=='H')) // .TH tag
      {
       strcpy(THtag,cur_string);
      }
     else
     if((cur_string[0]=='.')&&(cur_string[1]=='B')&&
       (cur_string[2]==' ')) // .B tag
      {
       SetCl(BOLD);
       text_outp(cur_string);
       SetCl(NORMAL);
      }
      else
      if((cur_string[0]=='.')&&(cur_string[1]=='N')&&
        (cur_string[2]=='L'))
       {
        putchar('\n');
        putchar(' ');
       }

     else
     {
       text_outp(cur_string); // print plane text
     }
    th_outp(cur_string, THtag);
    /* END of TAGs processing */

    free(cur_string);
    free(THtag);
    return 0;
}