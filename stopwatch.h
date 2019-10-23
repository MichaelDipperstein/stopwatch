/***************************************************************************
*                         Simple Stopwatch Library
*
*   File    : stopwatch.h
*   Purpose : Header for library implementing basic stopwatch functionality.
*             Contains type definitions, prototypes, and a class definition
*             to be used by programs linking to the Stopwatch library.
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
#ifndef STOPWATCH_H
#define STOPWATCH_H

/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <time.h>

/***************************************************************************
*                                CONSTANTS
***************************************************************************/
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/***************************************************************************
*                            TYPE DEFINITIONS
***************************************************************************/
typedef struct
{
    unsigned char isRunning;
    struct timespec startTime;
    struct timespec runningTime;
}  stopwatch_t;

#if defined __cplusplus
extern "C"
{
#endif

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
void StartTimer(stopwatch_t *stopWatch);    /* start or restart stopwatch */
void StopTimer(stopwatch_t *stopWatch);     /* stopwatch */
void ResumeTimer(stopwatch_t *stopWatch);   /* resume stopped watch */

/* returns stopwatch time in ms */
unsigned long ReadTimer(const stopwatch_t *stopWatch);

#if defined __cplusplus
}
#endif


#if defined __cplusplus
/* c++ class encapsulations */

/***************************************************************************
*                            CLASS DEFINITIONS
***************************************************************************/
class stopwatch_c
{
    public:
        stopwatch_c(void)
        {
            watchData.isRunning = FALSE;
            watchData.startTime.tv_sec = 0;
            watchData.startTime.tv_nsec = 0;
            watchData.runningTime.tv_sec = 0;
            watchData.runningTime.tv_nsec = 0;
        };

        ~stopwatch_c(void) {};

        void Start(void) {StartTimer(&watchData);};
        void Stop(void) {StopTimer(&watchData);};
        void Resume(void) {ResumeTimer(&watchData);};

        /* running time in ms last time if stopped */
        unsigned long Read(void) const
        {
            return ReadTimer(&watchData);
        };

    private:
        stopwatch_t watchData;
};
#endif /* defined __cplusplus */

#endif /* ndef STOPWATCH_H */
