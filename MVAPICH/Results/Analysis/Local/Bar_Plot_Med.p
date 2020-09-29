
set style data histograms
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,28"
set xlabel "Message Size (B)" font "Times-Roman,30"
set ylabel "Latency (us)" font "Times-Roman,30" 
set grid ytics lw 0.7 lt 0
set term postscript eps font "Times-Roman, 30" enhanced color
set output label.'.eps'

plot file using 2:xtic(1) title "Default-Block" lc rgb "#ef074c",\
 "" using 3 title "Default-Cyclic" lt rgb "#17b23e",\
 "" using 4 title "NB" lt rgb "#0707c1",\
 "" using 5 title "RingNB" lt rgb "#fcfc05"