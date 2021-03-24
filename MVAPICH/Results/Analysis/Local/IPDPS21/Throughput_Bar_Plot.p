
set style data histograms
set style fill solid border lt -1
set key left top Left samplen 1 reverse
set key font "Times-Roman,28"
set xlabel "Message Size" font "Times-Roman,30"
set ylabel "Throughput (MB/s)" font "Times-Roman,30" 
set grid ytics lw 0.7 lt 0
set term postscript eps font "Times-Roman, 30" enhanced color
set output 'throughputs.eps'
set xtic font "Times-Roman,26"
set yrange [:12250]
set size 1.5, 1


plot "throughputs_bar_data.dat" using 2:xtic(1) title "Ping-pong throughput" lc rgb "#A1F1C3",\
 "" using 3 title "encryption throughput" lt rgb "#2DBF3F"
