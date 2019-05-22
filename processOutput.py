#!/usr/bin/env python3

'''
Ao executar o toy2dac serão gerados arquivos com o nome timeTraceOutN.out,
onde N é o mype do processo que o gerou. Para executar o script python
é só reunir esses arquivos num mesmo diretório e executar:
  $ python3 processOutput.py timeTraceOut*.out
'''

import sys
import numpy as np
import matplotlib.pyplot as plt

codeLines = [42, 164, 276, 278, "all"]

defaultColor = 'gray'

regionColors = {
  ("bcast_s", "bcast_e"): 'red',
  ("grad_s", "grad_e"): 'green',
}

def loadFiles():
  times = []
  traces = []
  for i in sys.argv[1:]:
    ptime = []
    ptrace = []
    f = open(i)
    for j in f:
      jVec = j.strip().split(",")
      if(jVec[1] not in codeLines and "all" not in codeLines):
        continue
      ptime.append(int(jVec[0]))
      ptrace.append(jVec[1])
    f.close()
    times.append(np.array(ptime))
    traces.append(ptrace)
  return times, traces

def checkTraces(traces):
  for t in traces:
    for t2 in traces:
      if(t != t2):
        return 0
  return 1
          

def generateTimeline(times, traces):
  start_time = times[0][0]
  for i in times:
    start_time = min(start_time, i[0])
  for i in times:
    i -= start_time
  

  for i in range(len(times)):
    xranges = []
    colors = []
    for j in range(len(times[i]) - 1):
      xranges.append((times[i][j], times[i][j + 1] - times[i][j]))
      if((traces[i][j], traces[i][j + 1]) not in regionColors):
        colors.append(defaultColor)
      else:
        colors.append(regionColors[(traces[i][j], traces[i][j + 1])])
    yield (xranges, colors)



if __name__ == "__main__":
  times, traces = loadFiles()
  print("Traces: %d" % checkTraces(traces))

  yLine = -0.25 
  for (xranges, colors) in generateTimeline(times, traces):
    plt.broken_barh(xranges, [yLine, 0.5], facecolors = colors, zorder=3)
    yLine += 1
  
  plt.yticks(range(int(yLine + 0.25)))
  plt.ylabel("Process")
  plt.xlabel(r'Time ($\mu s$)')
  plt.grid(zorder=0, axis='x', linestyle='--')
  plt.show()
