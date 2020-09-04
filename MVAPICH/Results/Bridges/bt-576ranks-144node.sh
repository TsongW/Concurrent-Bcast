#!/bin/bash
#SBATCH -p RM
#SBATCH -t 2:00:00
#SBATCH -N 144

set -x 


#export MV2_SHOW_CPU_BINDING=1
export MV2_ENABLE_AFFINITY=1
export MV2_CPU_BINDING_POLICY=hybrid
export MV2_HYBRID_BINDING_POLICY=spread 
export OMP_NUM_THREADS=1





export LD_LIBRARY_PATH=/home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/lib

time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-1
time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-2
time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-3
time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-4
time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-5

time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-6
time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-7
time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-8
time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-9
time /home/abu/ics-2020/unencrypted-base/mvapich2-2.3.2/pro-un-base/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-base-log-10




export LD_LIBRARY_PATH=/home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/lib:/home/abu/boringssl-master/build/crypto

time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-1 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-2
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-3
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-4
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-5

time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-6 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-7
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-8
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-9
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-naive/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-naive-log-10



export LD_LIBRARY_PATH=/home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/lib:/home/abu/boringssl-master/build/crypto

time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-1 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-2 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-3 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-4 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-5 

time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-6 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-7 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-8 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-9 
time /home/abu/ics-2020/psc-bridge-mvapich2-2.3.2/pro-cryptmpi/bin/mpiexec -n 576 -ppn 4 ./bt.D.576 2> july-30-bt.D.576-cryptmpi-log-10 

 
