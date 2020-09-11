set colorsequence default
set xtics ("256" 256, "512" 512, "1K" 1024, "2K" 2048, "4K" 4096, "8K" 8192) rotate by 90 center offset 0, -1
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



plot "Default-Block" title "Default-Block" with lp lt rgb "black" pt 7 ps 2 lw 3 dt 3, "Default-Cyclic" title "Default-Cyclic" with lp lt rgb "red" pt 3 ps 2 lw 3, "NB" title "NB" with lp lt rgb "green" pt 5 ps 2 lw 3 dt 5, "RingNB" title "RingNB" with lp lt rgb "blue" pt 8 ps 2 lw 3 dt 2
