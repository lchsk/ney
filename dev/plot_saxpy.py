import pandas as pd
import matplotlib.pyplot as pl
import matplotlib.patches as mpatches
import numpy as np
import os, sys

pl.xlabel('Vector length')

pl.grid(True)

c1 = 'red'
c2 = 'green'
c3 = 'blue'
c4 = 'yellow'
c5 = 'purple'
c6 = 'brown'

EXPERIMENT = sys.argv[1]
VAR = 'TIME'

if len(sys.argv) == 3:
    VAR = sys.argv[2]

if VAR == 'TIME':
    pl.ylabel('Time [s]')
elif VAR == 'FLOP':
    pl.ylabel('GFlops')

d = pd.read_csv("saxpy")

pl.title('SAXPY benchmark running on different systems')

l1 = mpatches.Patch(color=c1, label='Intel i5')
l2 = mpatches.Patch(color=c2, label='Intel Xeon')
l3 = mpatches.Patch(color=c3, label='Intel Xeon Phi')
l4 = mpatches.Patch(color=c4, label='Ge Force')
l5 = mpatches.Patch(color=c5, label='Tesla')
pl.legend(handles=[l1, l2, l3, l4, l5], prop={'size': 12}, loc=0)

exp = d.ix[d['FUNC'] == EXPERIMENT]

pl.ylim(-0.05, max(exp[VAR]) * 1.1)
pl.xlim(10**6 * 0.9, 10**8 * 1.1)
pl.semilogx()

i5 = exp.ix[exp['PROC'] == 'i5']
xeon = exp.ix[exp['PROC'] == 'xeon']
mic = exp.ix[exp['PROC'] == 'mic']
geforce = exp.ix[exp['PROC'] == 'geforce']
tesla = exp.ix[exp['PROC'] == 'tesla']

pl.plot(i5['SIZE'], i5[VAR], marker='o', color=c1, lw=2)
pl.plot(xeon['SIZE'], xeon[VAR], marker='o', color=c2, lw=2)
pl.plot(mic['SIZE'], mic[VAR], marker='o', color=c3, lw=2)
pl.plot(geforce['SIZE'], geforce[VAR], marker='o', color=c4, lw=2)
pl.plot(tesla['SIZE'], tesla[VAR], marker='o', color=c5, lw=2)

pl.show()
