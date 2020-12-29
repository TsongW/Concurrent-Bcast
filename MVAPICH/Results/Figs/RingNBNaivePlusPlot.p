set tics font "Times-Roman,20"
set key left top Left box 3
set key font "Times-Roman,20"
set xlabel "Message Size (B)" font "Times-Roman,23" offset 0, -1
set ylabel "Latency (us)" font "Times-Roman,23" offset -3, 0

set term postscript eps font "Times-Roman" enhanced color
set output label.'.eps'
set lmargin 20
set rmargin 5
set bmargin 5
set tmargin 2


plot "Default" title "Default" with lp lt rgb "black" pt 7 ps 2, "Unencrypted_RingNB" title "Unencrypted ring non blocked" with lp lt rgb "red" pt 3 ps 2 lw 3, "Naive_RingNB" title "Naive ring non blocked" with lp lt rgb "green" pt 6 ps 2 lw 3, "Naive_Plus_RingNB" title "Naive+ ring non blocked" with lp lt rgb "blue" pt 5 ps 2 lw 3
