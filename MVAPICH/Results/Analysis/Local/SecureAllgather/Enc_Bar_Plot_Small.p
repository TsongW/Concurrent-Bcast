set size 1.25, 1.0
set style data histograms
set style fill pattern border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,30"
set xlabel "Message Size" font "Times-Roman,35"
set ylabel "Latency (us)" font "Times-Roman,35"
set grid ytics lw 0.7 lt rgb "#939393"
#set yrange [:140]

set term postscript eps font "Times-Roman, 35" enhanced color
set output label.'.eps'


plot file using 3:xtic(1) title "O-RD" lc rgb "#edf8b1" fillstyle pattern 3,\
 "" using 4 title "O-RD2" lt rgb "#7fcdbb" fillstyle pattern 3,\
 "" using 9 title "C-HS" lt rgb "#2c7fb8" fillstyle pattern 3

