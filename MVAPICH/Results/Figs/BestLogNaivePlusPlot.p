set tics font "Times-Roman,20"
set key left top Left box 3
set key font "Times-Roman,20"
set xlabel "Message Size (B)" font "Times-Roman,23" offset 0, -1
set ylabel "Latency (us)" font "Times-Roman,23" offset -3, 0

set xrange [0:22]
set yrange [min_y:max_y]
set xtics ("1" 0, "4" 2, "16" 4, "64" 6, "256" 8, "1K" 10, "4K" 12, "16K" 14, "64K" 16, "256K" 18, "1M" 20)
set ytics ("16" 4, "64" 6, "256" 8, "1024" 10, "4096" 12, "16384" 14, "65536" 16)

set xtics nomirror
set ytics nomirror

set term postscript eps font "Times-Roman" enhanced color
set output label.'.eps'
set lmargin 20
set rmargin 5
set bmargin 5
set tmargin 2

plot "Default" title "Unencrypted default" with lp lt rgb "black" pt 7 ps 2, "NB" title "Non blocked" with lp lt rgb "red" pt 3 ps 2 lw 3, "RingNB" title "Ring non blocked" with lp lt rgb "green" pt 5 ps 2 lw 3