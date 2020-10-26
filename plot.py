import matplotlib.pyplot as plt
import itertools
import numpy as np
import collections
import matplotlib
from cycler import cycler

matplotlib.rc('xtick', labelsize=14) 
matplotlib.rc('ytick', labelsize=14) 
matplotlib.rc('font', size=14) 
matplotlib.rc('axes', labelsize=14) 
matplotlib.rc('lines', linewidth=3) 
plt.rcParams['legend.framealpha'] = 0.0
plt.rcParams['legend.fancybox'] = False
NUM_OF_EXECUTIONS=5
parameters = [
    [0,1],
    [
        # "knapPI_1_10000_1000_1",
        "knapPI_1_1000_1000_1",
        "knapPI_1_100_1000_1",
        # "knapPI_1_2000_1000_1",
        "knapPI_1_200_1000_1",
        # "knapPI_1_5000_1000_1",
        "knapPI_1_500_1000_1",
        # "knapPI_2_10000_1000_1",
        "knapPI_2_1000_1000_1",
        "knapPI_2_100_1000_1",
        # "knapPI_2_2000_1000_1",
        "knapPI_2_200_1000_1",
        # "knapPI_2_5000_1000_1",
        "knapPI_2_500_1000_1",
        # "knapPI_3_10000_1000_1",
        "knapPI_3_1000_1000_1",
        "knapPI_3_100_1000_1",
        # "knapPI_3_2000_1000_1",
        "knapPI_3_200_1000_1",
        # "knapPI_3_5000_1000_1",
        "knapPI_3_500_1000_1",
    ],
]

combinations = itertools.product(*parameters)

def parse_result_file(f):
    ew = {'iterations':[],'best_value':0,'time':0}
    j = 0
    for line in f:
        line= line.rstrip('\n')
        line = line.split(' ')
        if line[0].isnumeric():
            ew['iterations'].append(int(line[1]))
        else:
            if j == 0:
                ew['best_value'] = int(line[1])
            else:
                ew['time'] = float(line[1])
            j+=1
    ew['iterations'] = np.array(ew['iterations'])
    return ew
results = collections.defaultdict(dict)
for c in combinations:
    current_instance_dicts = []
    for i in list(range(1,NUM_OF_EXECUTIONS+1)):
        fin = open(f"data/results/{c[0]}_{c[1]}_{i}.txt")
        current_instance_dicts.append(parse_result_file(fin))
    # np.s[result['iterations'] for result in current_instance_dicts]
    mean_result = {}
    mean_result['iterations']=np.add.reduce([result['iterations'] for result in current_instance_dicts])/len(current_instance_dicts)
    mean_result['best_value']=np.sum([result['best_value'] for result in current_instance_dicts])/len(current_instance_dicts)
    mean_result['time']=np.sum([result['time'] for result in current_instance_dicts])/len(current_instance_dicts)
    results[c[1]][c[0]] = mean_result
    print(mean_result)
    print(results)

print("| Instância | Usando PR | Função Objetivo | Tempo (s)|")
for i, pr in results.items():
    for j, result in pr.items():
        print(f"| {i} | {'Não' if j==0 else 'Sim'} | {result['best_value']} | {result['time']:.2f}|")


fig, ax = plt.subplots()

plt.gca().set_prop_cycle(cycler('color', ['#33a01c','#fb9a99','#e31a1c','#fdbf6f']))
instance = "knapPI_1_500_1000_1"
for i in [0,1]:
    ax.plot(results[instance][i]['iterations'],label="GRASP-PR" if i == 1 else "GRASP")
ax.legend()


plt.show()
fig.savefig(f"doc/knapPI_1_500_1000_1_iterations.eps",bbox_inches='tight')
