/***************************************************************************
*                      Sample Usage of Stopwatch Library
*
*   File    : sample.c
*   Purpose : This file provides samples demonstrating the use of each of
*             the stopwatch C functions.
*   Author  : Michael Dipperstein
*   Date    : July 7, 2011
*
****************************************************************************
*
* Stopwatch: A POSIX C/C++ Stopwatch Library
* Copyright (C) 2011 by Michael Dipperstein (mdipperstein@gmail.com)
*
* This file is part of the stopwatch library.
*
* The stopwatch library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 3 of the
* License, or (at your option) any later version.
*
* The stopwatch library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
* General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************/

/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include "stopwatch.h"
#include <stdio.h>

/* make sleep function work for linux and ms-windows (at least with mingw) */
#ifdef WIN32
#include <windows.h> 
#define sleep(s)        Sleep((s) * 1000)
#else
#include <unistd.h>
#endif

/***************************************************************************
*   Function   : main
*   Description: This is the main function for this program, it calls all
*                of the functions in the stopwatch library.  There's 
*                nothing really interesting about the code.  It just
*                sleeps for periods and reports the stopwatch time.
*   Parameters : None
*   Effects    : Stopwatch is run measuring various sleep cycles.
*   Returned   : 0 is always returned.
***************************************************************************/
int main()
{
    stopwatch_t stopWatch;
    int totalSleep;
    int i;

    printf("Measuring Sleep Time\n");
    
    /* verify free running */
    StartTimer(&stopWatch);
    sleep(3);
    totalSleep = 3000;
    printf("\tExpected: %d\tReported: %lu\n", totalSleep,
        ReadTimer(&stopWatch));
    sleep(3);
    totalSleep += 3000;
    printf("\tExpected: %d\tReported: %lu\n", totalSleep,
        ReadTimer(&stopWatch));

    /* stop and verify no change */
    StopTimer(&stopWatch);
    printf("Stopwatch Timer Stopped\n");
    sleep(3);
    printf("\tExpected: %d\tReported: %lu\n", totalSleep,
        ReadTimer(&stopWatch));

    /* resume and verify continuation */
    ResumeTimer(&stopWatch);
    printf("Stopwatch Timer Resumed\n");
    sleep(3);
    totalSleep += 3000;
    printf("\tExpected: %d\tReported: %lu\n", totalSleep,
        ReadTimer(&stopWatch));

    /* verify restart */
    StartTimer(&stopWatch);
    printf("Stopwatch Timer Restarted\n");
    sleep(3);
    totalSleep = 3000;
    printf("\tExpected: %d\tReported: %lu\n", totalSleep,
        ReadTimer(&stopWatch));

    /* should see extra ms, because loop + sleep > 1 second */
    printf("One Second Sleep Inside Loop (25 seconds)\n");
    for (i = 0; i < 25; i++)
    {
        sleep(1);
        totalSleep += 1000;
        printf("\tExpected: %d\tReported: %lu\n", totalSleep,
            ReadTimer(&stopWatch));
    }

    return 0;
}
