/***************************************************************************
*                      Sample Usage of Stopwatch Library
*
*   File    : sample.cpp
*   Purpose : This file provides samples demonstrating the use of each of
*             the stopwatch C++ class.
*   Author  : Michael Dipperstein
*   Date    : July 7, 2011
*
****************************************************************************
*
* Stopwatch: An ANSI C/C++ Stopwatch Library
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
#include <iostream>

/* make sleep function work for linux and ms-windows (at least with mingw) */
#ifdef _WIN32
#include <windows.h>
#define sleep(s)        Sleep((s) * 1000)
#else
#include <unistd.h>
#endif

using namespace std;

/***************************************************************************
*   Function   : main
*   Description: This is the main function for this program, it uses all
*                of the methods in the stopwatch class library.  There's
*                nothing really interesting about the code.  It just
*                sleeps for periods and reports the stopwatch time.
*   Parameters : argc - number of parameters
*                argv - parameter list
*   Effects    : Stopwatch is run measuring various sleep cycles.
*   Returned   : 0 is always returned.
***************************************************************************/
int main(int argc, char *argv[])
{
    stopwatch_c stopWatch;
    int totalSleep;

    cout << "Measuring Sleep Time" << endl;

    /* verify free running */
    stopWatch.Start();
    sleep(3);
    totalSleep = 3000;
    cout << "\tExpected: " << totalSleep << "\tReported: " << stopWatch.Read()
        << endl;
    sleep(3);
    totalSleep += 3000;
    cout << "\tExpected: " << totalSleep << "\tReported: " << stopWatch.Read()
        << endl;

    /* stop and verify no change */
    stopWatch.Stop();
    cout << "Stopwatch Timer Stopped" << endl;
    sleep(3);
    cout << "\tExpected: " << totalSleep << "\tReported: " << stopWatch.Read()
        << endl;

    /* resume and verify continuation */
    cout << "Stopwatch Timer Resumed" << endl;
    stopWatch.Resume();
    sleep(3);
    totalSleep += 3000;
    cout << "\tExpected: " << totalSleep << "\tReported: " << stopWatch.Read()
        << endl;

    /* verify restart */
    stopWatch.Start();
    cout << "Stopwatch Timer Restarted" << endl;
    sleep(3);
    totalSleep = 3000;
    cout << "\tExpected: " << totalSleep << "\tReported: " << stopWatch.Read()
        << endl;

    /* should see extra ms, because loop + sleep > 1 second */
    cout << "One Second Sleep Inside Loop (25 seconds)" << endl;
    for (int i = 0; i < 25; i++)
    {
        sleep(1);
        totalSleep += 1000;
        cout << "\tExpected: " << totalSleep << "\tReported: " <<
            stopWatch.Read() << endl;
    }

    return 0;
}
