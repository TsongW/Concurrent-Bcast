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
set ytics 20,25,180
set yrange[20:175]


#BLOCK:
plot file using 2:xtic(1) title "MVAPICH (Ring)" lc rgb "#ffffcc",\
 "" using 3 title "C-Ring" lt rgb "#a1dab4",\
 "" using 4 title "C-RD" lt rgb "#41b6c4",\
 "" using 6 title "C-HS" lt rgb "#225ea8"


#CYCLIC:

#plot file using 2:xtic(1) title "MVAPICH (Ring)" lt rgb "#e0f3db",\
# "" using 5 title "C-Ring" lt rgb "#a8ddb5",\
# "" using 7 title "HS1" lt rgb "#43a2ca",\

 
 
