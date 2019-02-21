\ SCIP STATISTICS
\   Problem name     : vrp
\   Variables        : 120 (120 binary, 0 integer, 0 implicit integer, 0 continuous)
\   Constraints      : 141
\   Obj. scale       : 1
\   Obj. offset      : 0
Minimize
 Obj: +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d
      +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d
      +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d
      +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d +0.8 x_%d_%d_%d
      +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d
      +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d
      +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d +2.1 x_%d_%d_%d
      +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d
      +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d
      +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d +3.5 x_%d_%d_%d
      +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d +3.3 x_%d_%d_%d
      +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d
Subject to
 a_%d: +0.8 x_%d_%d_%d +2.1 x_%d_%d_%d +3.5 x_%d_%d_%d +0.8 x_%d_%d_%d +1.4 x_%d_%d_%d +3.3 x_%d_%d_%d
  +2.1 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +3.5 x_%d_%d_%d +3.3 x_%d_%d_%d +1.4 x_%d_%d_%d <= +10
 a_%d: +0.8 x_%d_%d_%d +2.1 x_%d_%d_%d +3.5 x_%d_%d_%d +0.8 x_%d_%d_%d +1.4 x_%d_%d_%d +3.3 x_%d_%d_%d
  +2.1 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +3.5 x_%d_%d_%d +3.3 x_%d_%d_%d +1.4 x_%d_%d_%d <= +10
 a_%d: +0.8 x_%d_%d_%d +2.1 x_%d_%d_%d +3.5 x_%d_%d_%d +0.8 x_%d_%d_%d +1.4 x_%d_%d_%d +3.3 x_%d_%d_%d
  +2.1 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +3.5 x_%d_%d_%d +3.3 x_%d_%d_%d +1.4 x_%d_%d_%d <= +10
 a_%d: +0.8 x_%d_%d_%d +2.1 x_%d_%d_%d +3.5 x_%d_%d_%d +0.8 x_%d_%d_%d +1.4 x_%d_%d_%d +3.3 x_%d_%d_%d
  +2.1 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +3.5 x_%d_%d_%d +3.3 x_%d_%d_%d +1.4 x_%d_%d_%d <= +10
 a_%d: +0.8 x_%d_%d_%d +2.1 x_%d_%d_%d +3.5 x_%d_%d_%d +0.8 x_%d_%d_%d +1.4 x_%d_%d_%d +3.3 x_%d_%d_%d
  +2.1 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +3.5 x_%d_%d_%d +3.3 x_%d_%d_%d +1.4 x_%d_%d_%d <= +10
 a_%d: +0.8 x_%d_%d_%d +2.1 x_%d_%d_%d +3.5 x_%d_%d_%d +0.8 x_%d_%d_%d +1.4 x_%d_%d_%d +3.3 x_%d_%d_%d
  +2.1 x_%d_%d_%d +1.4 x_%d_%d_%d +1.4 x_%d_%d_%d +3.5 x_%d_%d_%d +3.3 x_%d_%d_%d +1.4 x_%d_%d_%d <= +10
 b_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 b_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 b_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 b_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 b_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 b_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 c_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 c_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 c_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 c_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 c_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 c_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 d_%d: +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d = +1
 d_%d: +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d = +1
 d_%d: +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d +1 y_%d_%d = +1
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 e_%d: +1 y_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 f_%d: +1 x_%d_%d_%d = +0
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +1 x_%d_%d_%d +1 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 g_%d: +2 x_%d_%d_%d <= +1
 c118: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c119: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c120: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c121: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c122: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c123: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c124: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c125: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c126: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c127: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c128: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c129: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c130: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c131: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c132: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c133: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c134: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c135: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c136: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c137: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c138: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c139: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c140: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
 c141: +1 x_%d_%d_%d +1 x_%d_%d_%d +1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d -1 x_%d_%d_%d = +0
Bounds
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= y_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
 0 <= x_%d_%d_%d <= 1
Binaries
 y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d
 y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d y_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
 x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d x_%d_%d_%d
End
