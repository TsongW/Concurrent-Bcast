
set style data histograms
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,28"
set xlabel "Message Size" font "Times-Roman,32"
set ylabel "Latency (us)" font "Times-Roman,32"
set grid ytics lw 0.7 lt 0
#set yrange [:135]

set term postscript eps font "Times-Roman, 32" enhanced color
set output label.'.eps'

plot file using 2:xtic(1) title "Naive Default" lc rgb "#EBFAEF",\
 "" using 3 title "Naive NB" lt rgb "#A1F1C3",\
 "" using 5 title "Naive+ Default" lt rgb "#2DBF3F",\
 "" using 6 title "Naive+ NB" lt rgb "#036144",\
 "" using 9 title "Encrypted ML-RD" lt rgb "#000000"


