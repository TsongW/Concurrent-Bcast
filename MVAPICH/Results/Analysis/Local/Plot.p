
set xtics x_tics
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


plot "Default-Block" title "Default-Block" with lp lt rgb "black" pt 7 ps 2, "Default-Cyclic" title "Default-Cyclic" with lp lt rgb "red" pt 3 ps 2 lw 3, "NB" title "NB" with lp lt rgb "green" pt 5 ps 2 lw 3, "RingNB" title "RingNB" with lp lt rgb "blue" pt 8 ps 2 lw 3

plot "Default-Block" title "Default-Block" with lp lt rgb "black" pt 7 ps 2 lw 3, "Default-Cyclic" title "Default-Cyclic" with lp lt rgb "red" pt 3 ps 2 lw 3, "NB" title "NB" with lp lt rgb "green" pt 5 ps 2 lw 3, "RingNB" title "RingNB" with lp lt rgb "blue" pt 8 ps 2 lw 3