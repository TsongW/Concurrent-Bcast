
set view map
set size 4, 1.5

set term postscript eps font "Times-Roman, 30" enhanced color
set output label.'.eps'

set pm3d interpolate 20, 20

set palette rgb 21,22,23
set dgrid3d
set xrange[:21]
set ytics ("Default-Block" 0, "Default-Cyclic" 1, "NB" 2, "RingNB" 3, "ML-Ring" 4, "ML-RD-Block" 5, "ML-RD-Cyclic" 6)
set xtics ("1B" 0, "2B" 1, "4B" 2, "8B" 3, "16B" 4, "32B" 5, "64B" 6, "128B" 7, "256B" 8, "512B" 9, "1KB" 10, "2KB" 11\
	, "4KB" 12, "8KB" 13, "16KB" 14, "32KB" 15, "64KB" 16, "128KB" 17, "256KB" 18, "512KB" 19, "1MB" 20, "2MB" 21)


splot file using 1:2:3 with pm3d

