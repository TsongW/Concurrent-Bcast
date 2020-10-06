
set style data histograms
set style fill pattern border lt -1
set key left top Left samplen 1 reverse
#set key horizontal top center samplen 1
set key font "Times-Roman,28"
set xlabel "Message Size" font "Times-Roman,32"
set ylabel "Latency (ms)" font "Times-Roman,32" 
set grid ytics lw 0.7 lt 0
set term postscript eps font "Times-Roman, 32" enhanced color
set output label.'.eps'
#set yrange [:400]


plot file using 2:xtic(1) title "Naive Default" lc rgb "#000000" fillstyle pattern 1,\
 "" using 4 title "Naive RingNB" lt rgb "#EBFAEF" fillstyle pattern 3,\
 "" using 5 title "Naive+ Default" lt rgb "#A1F1C3" fillstyle pattern 3,\
 "" using 7 title "Naive+ RingNB" lt rgb "#2DBF3F" fillstyle pattern 3,\
 "" using 8 title "Encrypted ML-Ring" lt rgb "#036144" fillstyle pattern 3,\
 "" using 9 title "Encrypted ML-RD" lt rgb "#000000" fillstyle pattern 3