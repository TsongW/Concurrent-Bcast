set size 1.25, 1.0
set style data histograms
set style fill pattern border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,30"
set xlabel "Message Size" font "Times-Roman,35"
set ylabel "Latency (us)" font "Times-Roman,35"
set grid ytics lw 0.7 lt rgb "#939393"
#set yrange [:140]

set term postscript eps font "Times-Roman, 35" enhanced color
set output label.'.eps'


plot file using 2:xtic(1) title "O-RDB" lc rgb "#f0f9e8" fillstyle pattern 3,\
 "" using 12 title "CO-RDB" lt rgb "#bae4bc" fillstyle pattern 3,\
 "" using 9 title "C-RDB" lt rgb "#7bccc4" fillstyle pattern 3,\
 "" using 10 title "Shmem-Leader" lt rgb "#2b8cbe" fillstyle pattern 3

