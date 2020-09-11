
set style data histograms
set style fill solid
set key left top
set key font "Times-Roman,20"
set xlabel "Message Size (B)" font "Times-Roman,23"
set ylabel "Latency (us)" font "Times-Roman,23" 
set grid ytics lw 1.5
set term postscript eps font "Times-Roman, 20" enhanced color
set output label.'.eps'

plot file using 2:xtic(1) title "Default-Block" lc rgb "red",\
 "" using 3 title "Default-Cyclic" lt rgb "green",\
 "" using 4 title "NB" lt rgb "blue",\
 "" using 5 title "RingNB" lt rgb "orange"