
set style data histograms
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,28"
set xlabel "Message Size" font "Times-Roman,32"
set ylabel "Latency (ms)" font "Times-Roman,32" 
set grid ytics lw 0.7 lt 0
set term postscript eps font "Times-Roman, 32" enhanced color
set output label.'.eps'
set xtic font "Times-Roman,26"

plot file using 2:xtic(1) title "Default" lc rgb "#EBFAEF",\
 "" using 3 title "NB" lt rgb "#A1F1C3",\
 "" using 6 title "ML-RD" lt rgb "#036144"
