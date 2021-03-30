set size 1.25, 1.0
set style data histograms
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,30"
set xlabel "Message Size" font "Times-Roman,35"
set ylabel "Latency (ms)" font "Times-Roman,35" 
set grid ytics lw 0.7 lt rgb "#939393"
set term postscript eps font "Times-Roman, 35" enhanced color
set output label.'.eps'

#BLOCK:
set ytics 0,30,160
set yrange[0:160]



#CYCLIC:
#set ytics 0,20,100
#set yrange[0:90]


#Block:
plot file using 8:xtic(1) title "HS2" lc rgb "#edf8b1" fillstyle pattern 3,\
 "" using 9 title "C-HS" lt rgb "#2c7fb8" fillstyle pattern 3

#Cyclic:
#plot file using 12:xtic(1) title "O-RD2" lc rgb "#f0f9e8" fillstyle pattern 3,\
# "" using 8 title "C-Ring" lt rgb "#bae4bc" fillstyle pattern 3,\
# "" using 10 title "HS1" lt rgb "#7bccc4" fillstyle pattern 3,\
# "" using 11 title "HS2" lt rgb "#2b8cbe" fillstyle pattern 3