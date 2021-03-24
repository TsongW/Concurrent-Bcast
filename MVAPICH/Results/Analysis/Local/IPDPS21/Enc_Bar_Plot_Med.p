set size 1.25, 1.0
set style data histograms
set style fill pattern border lt -1
set key left top Left samplen 1 reverse
#set key horizontal top center samplen 1
set key font "Times-Roman,30"
set xlabel "Message Size" font "Times-Roman,35"
set ylabel "Latency (ms)" font "Times-Roman,35" 
set grid ytics lw 0.7 lt rgb "#939393"
set term postscript eps font "Times-Roman, 35" enhanced color
set output label.'.eps'
#set yrange [:400]


#CYCLIC:
#set ytics 0,0.5,2.5
#set yrange[0:2.5]

#Block
plot file using 8:xtic(1) title "C-Ring" lc rgb "#f0f9e8" fillstyle pattern 3,\
 "" using 9 title "C-RD" lt rgb "#bae4bc" fillstyle pattern 3,\
 "" using 10 title "HS1" lt rgb "#7bccc4" fillstyle pattern 3,\
 "" using 11 title "HS2" lt rgb "#2b8cbe" fillstyle pattern 3

#Cyclic
#plot file using 8:xtic(1) title "C-Ring" lc rgb "#e0f3db" fillstyle pattern 3,\
# "" using 10 title "HS1" lt rgb "#a8ddb5" fillstyle pattern 3,\
# "" using 11 title "HS2" lt rgb "#43a2ca" fillstyle pattern 3
