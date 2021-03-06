#!/bin/bash

cd ~/NPB3.3.1/NPB3.3-MPI/
cat config/make.def.template | \
sed "s/MPIF77 = f77/MPIF77 = mpif90/g" | \
sed "s/MPICC = cc/MPICC = mpicc/g" | \
sed "s/FLINKFLAGS = -O/FLINKFLAGS = -O ..\/bin\/kernel_stats.o/g" | \
sed "s/CLINKFLAGS = -O/CLINKFLAGS = -O ..\/bin\/kernel_stats.o/g" > config/make.def


cp config/suite.def.template config/suite.def
np=4
for bench in bt cg ep ft is lu mg sp; do
    for size in A B C; do
        echo "$bench    $size    $np" >> config/suite.def
	done
done


cd ~/NPB3.3.1/NPB3.3-MPI
mkdir -p ../bin
cd bin
gcc -c ~/kernel_stats/kernel_stats.c
cd ../

make suite
