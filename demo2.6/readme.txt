======================================================================
  isp_demo.py
  
  A demonstration software of the guided local search algorithm
  for the irregular strip packing problem
  
  Date: 2010/10/12
  Author: Shunji Umetani <umetani@ist.osaka-u.ac.jp>
======================================================================

----------------------------------------------------------------------
  Summary
----------------------------------------------------------------------
The irregular strip packing problem (ISP) asks a given set of 
non-convex polygons to be placed without overlap within a rectangular 
container having a fixed width and a variable length, which is to be 
minimized.

In the following paper, we proposed a heuristic algorithm for ISP
 based on metaheuristics.

S.Umetani, M.Yagiura, S.Imahori, T.Imamichi, K.Nonobe and T.Ibaraki:
Solving the irregular strip packing problem via guided local search 
for overlap minimization, 
International Transactions in Operational Research, 16, 661-683, 2009.

This software demonstrates a part of process that our algorithm solves
some ISP instances.

----------------------------------------------------------------------
  How to use
----------------------------------------------------------------------
The main program is written by Python2.6.
This package includes the following files.

readme.txt: The instruction of this software in English
readme_jp.txt: The instruction of this software in Japanese
isp_demo.py: Main program
*.dat: The processing data of our algorithm for ISP instances

1. Install Python
This software requires installation of Python2.6.x for execution,
where we note that this software does not work under Python3.

2. Set path
Change the first line of "isp_demo.py" to indicate the executable
file of Python installed.

3. Execute demonstration software
Doubly click the icon of "isp_demo.py" and then the demonstration 
software starts with main and console windows.
(The console window may disappear if you change the extension of 
"isp_demo.py" to "isp_demo.pyw" before starting the demonstration
software.)

4. Main window
The main window includes five buttons: "load", "start", "step",
 "reset" and "quit", and two indicator "View interval" and "Window
 size".

  4-1. Load data file
  Click "load" button and then the window of loading file opens.
  Select a data file for example "swim.dat" and then the initial
  placement of polygons is illustrated in the main window.

  4-2. Start demonstration
  Click "start" button and then the demonstration starts.
  The current placement is illustrated in the left part of the main
   window and the best feasible placement is illustrated in the right
  part of the main window.
  Polygons colored yellow mean that have overlap with other polygon,
  and polygons colored blue mean that have no overlap.

  4-3. Stop and reset demonstration 
  Click "pause" button and then the demonstration temporary stops.
  Click "reset" button and then the demonstration is initialized.
  ("reset" button can click only when the demonstration stops.)

  4-4. Stepwise execute
  Click "step" button and then the demonstration proceeds stepwise.
  ("step" button can click only when the demonstration stops.)

  4-5. Quit demonstration
  Click "quit" button and then quit this demonstration software.

  4-6. View interval
  Slide "View interval" indicator to change the interval of frames.
  (The change of this parameter works imidiately)

  4-7. Window size
  Slide "Window size" indicator to change the size of the main window.
  (The change of this parameter only works after clicking "reset" or
  "load" button)

----------------------------------------------------------------------
  Computational result
----------------------------------------------------------------------

The data files of this demonstration are based on the computational 
results by HP xw6600/CT Workstation (CPU: Quad core Intel Xeon E5420 
2.50GHz, Memory 4GB) with the time limit of 1200 seconds.
We note that the computational results of this demonstration differ 
from the published article.

----------------------------------------------------------------------
  Misc
----------------------------------------------------------------------
1. We note that the demonstration does not show the whole of search
   process because it makes huge data file and long execution time.
   The placement of polygons sometimes change drastically because 
   of skipping a part of search process.

2. The indicated values in the lower part of the main window mean the 
   numbers of frames in the demonstration.

----------------------------------------------------------------------
  Copyright
----------------------------------------------------------------------
(C) 2010 Shunji Umetani, All rights reserved.

This software is free for non-commercial use. It may be copied,
modified and redistributed provided that this copyright notice is
preserved on all copies.

You may not use this software, in whole or in part, in support
of any commercial product without the express consent of the
author.

There is no warranty or other guarantee of fitness of this
software for any purpose.
======================================================================
