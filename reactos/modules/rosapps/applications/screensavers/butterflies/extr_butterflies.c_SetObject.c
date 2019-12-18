#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tex; int x; float y; int z; int spinzi; float flap; float fi; float yi; } ;

/* Variables and functions */
 TYPE_1__* obj ; 
 int rand () ; 

void SetObject(int loop)										// Sets The Initial Value Of Each Object (Random)
{
	obj[loop].tex=rand()%3;										// Texture Can Be One Of 3 Textures
	obj[loop].x=rand()%34-17.0f;								// Random x Value From -17.0f To 17.0f
	obj[loop].y=18.0f;											// Set y Position To 18 (Off Top Of Screen)
	obj[loop].z=-((rand()%30000/1000.0f)+10.0f);				// z Is A Random Value From -10.0f To -40.0f
	obj[loop].spinzi=(rand()%10000)/5000.0f-1.0f;				// spinzi Is A Random Value From -1.0f To 1.0f
	obj[loop].flap=0.0f;										// flap Starts Off At 0.0f;
	obj[loop].fi=0.05f+(rand()%100)/1000.0f;					// fi Is A Random Value From 0.05f To 0.15f
	obj[loop].yi=0.001f+(rand()%1000)/10000.0f;					// yi Is A Random Value From 0.001f To 0.101f
}