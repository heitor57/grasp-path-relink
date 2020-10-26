import os
import multiprocessing
from concurrent.futures import ProcessPoolExecutor
from tqdm import tqdm

def run_parallel(func, args,chunksize = None,use_tqdm=True):
    executor = ProcessPoolExecutor()
    num_args = len(args)
    if not chunksize:
        chunksize = int(num_args/multiprocessing.cpu_count())
    if use_tqdm:
        ff = tqdm
    else:
        ff = lambda x,*y,**z: x 
    results = [i for i in ff(executor.map(func,*list(zip(*args)),chunksize=chunksize),total=num_args)]
    return results

import itertools
NUM_OF_EXECUTIONS = 5

parameters = [
    [
        # "knapPI_1_10000_1000_1",
        # "knapPI_1_1000_1000_1",
        "knapPI_1_100_1000_1",
        # "knapPI_1_2000_1000_1",
        "knapPI_1_200_1000_1",
        # "knapPI_1_5000_1000_1",
        # "knapPI_1_500_1000_1",
        # "knapPI_2_10000_1000_1",
        # "knapPI_2_1000_1000_1",
        # "knapPI_2_100_1000_1",
        # "knapPI_2_2000_1000_1",
        # "knapPI_2_200_1000_1",
        # "knapPI_2_5000_1000_1",
        # "knapPI_2_500_1000_1",
        # "knapPI_3_10000_1000_1",
        # "knapPI_3_1000_1000_1",
        # "knapPI_3_100_1000_1",
        # "knapPI_3_2000_1000_1",
        # "knapPI_3_200_1000_1",
        # "knapPI_3_5000_1000_1",
        # "knapPI_3_500_1000_1",
    ],
    list(range(1,NUM_OF_EXECUTIONS+1)),
]
combinations = itertools.product(*parameters)
args = [(f'./run data/large_scale/{c[0]} {c[0]+"_"+str(c[1])}',)
        for c in combinations]
# print(args)
run_parallel(os.system,args,chunksize=1)
