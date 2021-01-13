set size 1.25, 1.0
set style data histograms
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,30"
set xlabel "Message Size" font "Times-Roman,35"
set ylabel "Latency (ms)" font "Times-Roman,35" 
set grid ytics lw 0.7 lt rgb "#939393"
set term postscript eps font "Times-Roman, 35" enhanced color
set output label.'.eps'



#Block:
plot file using 5:xtic(1) title "O-Ring" lc rgb "#f0f9e8" fillstyle pattern 3,\
 "" using 8 title "C-Ring" lt rgb "#bae4bc" fillstyle pattern 3,\
 "" using 9 title "C-RDB" lt rgb "#7bccc4" fillstyle pattern 3,\
 "" using 10 title "Shmem-Leader" lt rgb "#43a2ca" fillstyle pattern 3,\
 "" using 11 title "DE-Shmem" lt rgb "#0868ac" fillstyle pattern 3

#Cyclic:
#plot file using 7:xtic(1) title "Naive+ RingNB" lc rgb "#f0f9e8" fillstyle pattern 3,\
# "" using 11 title "Naive+ RDB" lt rgb "#bae4bc" fillstyle pattern 3,\
# "" using 8 title "C-Ring" lt rgb "#7bccc4" fillstyle pattern 3,\
# "" using 10 title "ShMem-NB" lt rgb "#2b8cbe" fillstyle pattern 3