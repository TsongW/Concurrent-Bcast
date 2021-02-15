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

set ytics 0,3,18
set yrange[0:18]

plot file using 2:xtic(1) title "MVAPICH (RD)" lc rgb "#e0f3db",\
 "" using 5 title "C-RD" lt rgb "#a8ddb5",\
 "" using 6 title "HS1" lt rgb "#43a2ca"