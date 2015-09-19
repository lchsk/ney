import pandas as pd
import matplotlib.pyplot as pl
import matplotlib.patches as mpatches
import numpy as np
import os, sys

pl.xlabel('File size')

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

d = pd.read_csv("charcount")

pl.title('Character count running on different systems')

l1 = mpatches.Patch(color=c1, label='Library / Intel i5')
l2 = mpatches.Patch(color=c2, label='Library / Intel Xeon')
l3 = mpatches.Patch(color=c3, label='Library / Intel Xeon Phi')
l4 = mpatches.Patch(color=c4, label='Library / Ge Force')
l5 = mpatches.Patch(color=c5, label='Library / Tesla')

l6 = mpatches.Patch(color=c1, label='Bespoke / Intel i5', ls='dashed', fill=False)
l7 = mpatches.Patch(color=c2, label='Bespoke / Intel Xeon', ls='dashed', fill=False)
l8 = mpatches.Patch(color=c3, label='Bespoke / Intel Xeon Phi', ls='dashed', fill=False)

pl.legend(handles=[l1, l2, l3, l4, l5, l6, l7, l8], prop={'size': 12}, loc=0)

exp1 = d.ix[d['FUNC'] == 'charcount']
exp2 = d.ix[d['FUNC'] == 'ver2']


pl.ylim(-2, max(exp1[VAR]) * 1.1)
pl.xlim(1.8, 4.2)
pl.xticks([2, 3, 4], ['100 MB', '1 GB', '5 GB'])

i5 = exp1.ix[exp1['PROC'] == 'i5']
xeon = exp1.ix[exp1['PROC'] == 'xeon']
mic = exp1.ix[exp1['PROC'] == 'mic']
geforce = exp1.ix[exp1['PROC'] == 'geforce']
tesla = exp1.ix[exp1['PROC'] == 'tesla']

i5_2 = exp2.ix[exp2['PROC'] == 'i5']
xeon_2 = exp2.ix[exp2['PROC'] == 'xeon']
mic_2 = exp2.ix[exp2['PROC'] == 'mic']

pl.plot(i5['SIZE'], i5[VAR], marker='o', color=c1, lw=2)
pl.plot(xeon['SIZE'], xeon[VAR], marker='o', color=c2, lw=2)
pl.plot(mic['SIZE'], mic[VAR], marker='o', color=c3, lw=2)
pl.plot(geforce['SIZE'], geforce[VAR], marker='o', color=c4, lw=2)
pl.plot(tesla['SIZE'], tesla[VAR], marker='o', color=c5, lw=2)

pl.plot(i5_2['SIZE'], i5_2[VAR], marker='o', color=c1, lw=2, ls='dashed')
pl.plot(xeon_2['SIZE'], xeon_2[VAR], marker='o', color=c2, lw=2, ls='dashed')
pl.plot(mic_2['SIZE'], mic_2[VAR], marker='o', color=c3, lw=2, ls='dashed')

pl.show()
