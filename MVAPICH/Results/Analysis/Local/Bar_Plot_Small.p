set size 1.25, 1.0
set style data histograms
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,30"
set xlabel "Message Size" font "Times-Roman,35"
set ylabel "Latency (us)" font "Times-Roman,35" 
set grid ytics lw 0.7 lt 0
set term postscript eps font "Times-Roman, 35" enhanced color
set output label.'.eps'


plot file using 2:xtic(1) title "RDB" lc rgb "#e0f3db",\
 "" using 6 title "C-RDB" lt rgb "#a8ddb5",\
 "" using 7 title "ShMem-NB" lt rgb "#43a2ca"
