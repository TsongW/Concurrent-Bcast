
set style data histograms
set style fill solid border lt -1
#set key left top Left samplen 1 reverse
set key horizontal top center samplen 1
set key font "Times-Roman,25"
set xlabel "Message Size" font "Times-Roman,30"
set ylabel "Latency (us)" font "Times-Roman,30" 
set grid ytics lw 0.7 lt 0
set term postscript eps font "Times-Roman, 30" enhanced color
set output label.'.eps'
set yrange [:400]


plot file using 2:xtic(1) title "Default-Block" lc rgb "#EBFAEF",\
 "" using 3 title "Default-Cyclic" lt rgb "#A1F1C3",\
 "" using 4 title "NB" lt rgb "#2DBF3F",\
 "" using 5 title "RingNB" lt rgb "#036144"