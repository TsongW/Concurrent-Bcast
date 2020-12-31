
set key left top Left samplen 1 reverse
set key font "Times-Roman,28"
set xlabel "Message Size" font "Times-Roman,30"
set ylabel "Throughput (MB/s)" font "Times-Roman,30" 
set grid ytics lw 0.7 lt rgb "#D4D4D4"
set term postscript eps font "Times-Roman, 30" enhanced color
set output 'throughputs.eps'
set xtic font "Times-Roman,26"
set ytics 3500,1500 font "Times-Roman,26"
set yrange [:12250]
set size 1.5, 1


set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 6 \
    pointtype 2 pointsize 3

set style line 2 \
    linecolor rgb '#dd181f' \
    linetype 7 linewidth 4 \
    pointtype 5 pointsize 2

plot "throughputs_bar_data.dat" using 2:xtic(1) title "ping-pong" w lp ls 1,\
 "" using 3 title "encryption" with lp ls 2 dt 2


