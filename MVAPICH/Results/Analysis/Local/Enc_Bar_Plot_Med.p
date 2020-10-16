
set style data histograms
set style fill pattern border lt -1
set key left top Left samplen 1 reverse
#set key horizontal top center samplen 1
set key font "Times-Roman,28"
set xlabel "Message Size" font "Times-Roman,32"
set ylabel "Latency (ms)" font "Times-Roman,32" 
set grid ytics lw 0.7 lt 0
set term postscript eps font "Times-Roman, 30" enhanced color
set output label.'.eps'
#set yrange [:400]


plot file using 5:xtic(1) title "Naive+ RDB" lc rgb "#f0f9e8" fillstyle pattern 3,\
 "" using 7 title "Naive+ RingNB" lt rgb "#bae4bc" fillstyle pattern 3,\
 "" using 8 title "C-Ring" lt rgb "#7bccc4" fillstyle pattern 3,\
 "" using 10 title "C-RDB" lt rgb "#43a2ca" fillstyle pattern 3,\
 "" using 12 title "ShMem-NB" lt rgb "#0868ac" fillstyle pattern 3

