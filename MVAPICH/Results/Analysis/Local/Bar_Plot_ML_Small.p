
set style data histograms
set style fill solid border lt -1
set key horizontal top center samplen 1

set key font "Times-Roman,25"
set xlabel "Message Size" font "Times-Roman,30"
set ylabel "Latency (us)" font "Times-Roman,30"
set grid ytics lw 0.7 lt 0
#set axis nomirror
set yrange [:160]

set term postscript eps font "Times-Roman, 30" enhanced color
set output label.'.eps'

plot file using 2:xtic(1) title "Default-Block" lc rgb "#EBFAEF",\
 "" using 3 title "ML-Ring" lt rgb "#A1F1C3",\
 "" using 4 title "ML-RD-Blocked" lt rgb "#2DBF3F",\
  "" using 5 title "ML-RD-Cyclic" lt rgb "#036144"
