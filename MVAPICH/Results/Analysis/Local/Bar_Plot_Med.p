set style data histograms
set size 1.25, 1.0
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,30"
set xlabel "Message Size" font "Times-Roman,35"
set ylabel "Latency (ms)" font "Times-Roman,35" 
set grid ytics lw 0.7 lt rgb "#939393"
set term postscript eps font "Times-Roman, 35" enhanced color
set output label.'.eps'


plot file using 2:xtic(1) title "MVAPICH (Ring)" lc rgb "#f0f9e8",\
 "" using 5 title "C-Ring" lt rgb "#bae4bc",\
 "" using 6 title "C-RDB" lt rgb "#7bccc4",\
 "" using 7 title "Shmem-Leader" lt rgb "#2b8cbe"