/***************************************************************************
*                         Simple Stopwatch Library
*
*   File    : stopwatch.h
*   Purpose : This file implements a POSIX C library providing basic
*             stopwatch functionality.  The library attempts to maintain
*             microsecond accuracy for timing, but reports values in
*             milliseconds.  The actual accuracy is platform dependent.
*   Author  : Michael Dipperstein
*   Date    : July 7, 2011
*
****************************************************************************
*
* Stopwatch: A POSIX C/C++ Stopwatch Library
* Copyright (C) 2011 by Michael Dipperstein (mdipper@alumni.cs.ucsb.edu)
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
#include <time.h>

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/***************************************************************************
*   Function   : StartTimer
*   Description: This function starts or restarts a stopwatch timer.
*   Parameters : stopWatch - pointer to the stopwatch_t structure
*                containing the timer data.
*   Effects    : The stopwatch's start time is set to the current time,
*                any old accumulated time is cleared, and the timer's
*                running flag is set.
*   Returned   : None
***************************************************************************/
void StartTimer(stopwatch_t *stopWatch)
{
    stopWatch->isRunning = TRUE;
    clock_gettime(CLOCK_MONOTONIC, &stopWatch->startTime);
    stopWatch->runningTime.tv_sec = 0;
    stopWatch->runningTime.tv_nsec = 0;
}

/***************************************************************************
*   Function   : StopTimer
*   Description: This function stops a stopwatch timer.  The time that the
*                timer has been running is saved so that the time count may
*                be resumed.
*   Parameters : stopWatch - pointer to the stopwatch_t structure
*                containing the timer data.
*   Effects    : The stopwatch's total run time is saved, the previous
*                start time and the running flag are cleared.
*   Returned   : None
***************************************************************************/
void StopTimer(stopwatch_t *stopWatch)
{
    struct timespec now;

    if (FALSE == stopWatch->isRunning)
    {
        return;
    }

    stopWatch->isRunning = FALSE;
    clock_gettime(CLOCK_MONOTONIC, &now);

    /* update running time */
    stopWatch->runningTime.tv_sec +=
        (now.tv_sec - stopWatch->startTime.tv_sec);

    if (now.tv_nsec < stopWatch->startTime.tv_nsec)
    {
        /* borrow second */
        now.tv_nsec += 1000000000;
        stopWatch->runningTime.tv_sec -= 1;
    }

    stopWatch->runningTime.tv_nsec +=
        (now.tv_nsec - stopWatch->startTime.tv_nsec);
    
    stopWatch->startTime.tv_sec = 0;
    stopWatch->startTime.tv_nsec = 0;
}

/***************************************************************************
*   Function   : ResumeTimer
*   Description: This function resumes a stopped stopwatch timer.  Time
*                from previous runs will be added to the time accumulated
*                from this point on.
*   Parameters : stopWatch - pointer to the stopwatch_t structure
*                containing the timer data.
*   Effects    : The stopwatch's start time is set to the current time,
*                and the timer's running flag is set.
*   Returned   : None
***************************************************************************/
void ResumeTimer(stopwatch_t *stopWatch)
{
    if (FALSE == stopWatch->isRunning)
    {
        stopWatch->isRunning = TRUE;
        clock_gettime(CLOCK_MONOTONIC, &stopWatch->startTime);
    }
}

/***************************************************************************
*   Function   : ReadTimer
*   Description: This function returns the total time the stopwatch has
*                been running.
*   Parameters : stopWatch - pointer to the stopwatch_t structure
*                containing the timer data.
*   Effects    : None
*   Returned   : The total time the stopwatch has been running in
*                milliseconds.  If the stopwatch is stopped, the amount of
*                time accumulated prior to stopping the stopwatch is
*                returned.
***************************************************************************/
unsigned long ReadTimer(const stopwatch_t *stopWatch)
{
    unsigned long delta;
    struct timespec now;

    if (FALSE == stopWatch->isRunning)
    {
        return (stopWatch->runningTime.tv_sec * 1000) +
            (stopWatch->runningTime.tv_nsec / 1000000);
    }

    clock_gettime(CLOCK_MONOTONIC, &now);

    /* update running time */
    if (now.tv_nsec < stopWatch->startTime.tv_nsec)
    {
        /* borrow second */
        now.tv_nsec += 1000000000;
        now.tv_sec -= 1;
    }

    delta = ((now.tv_sec - stopWatch->startTime.tv_sec) +
        stopWatch->runningTime.tv_sec) * 1000;

    delta += ((now.tv_nsec - stopWatch->startTime.tv_nsec) +
        stopWatch->runningTime.tv_nsec) / 1000000;
 
    return delta;
}
