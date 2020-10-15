
set style data histograms
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,28"
set xlabel "Message Size" font "Times-Roman,32"
set ylabel "Latency (us)" font "Times-Roman,32" 
set grid ytics lw 0.7 lt 0
set term postscript eps font "Times-Roman, 32" enhanced color
set output label.'.eps'
set xtic font "Times-Roman,26"

plot file using 2:xtic(1) title "Default (RDB)" lc rgb "#e0f3db",\
 "" using 6 title "ML-RDB" lt rgb "#a8ddb5",\
 "" using 7 title "Shared-Memory" lt rgb "#43a2ca"
