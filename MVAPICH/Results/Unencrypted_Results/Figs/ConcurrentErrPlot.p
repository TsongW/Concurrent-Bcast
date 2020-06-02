set tics font ",17"
set key horizontal Left box outside
set key font ",20" height 1. width 1.7 spacing 1. 

set xlabel "Message size" font ",24" offset 0, -1
set ylabel "Relative error (%)" font ",24" offset -3, 0

set xtics nomirror
set ytics nomirror
set xtics ("1B" 0, "16B" 2, "256B" 4, "1KB" 6, "4KB" 8, "16KB" 10, "64KB" 12, "256KB" 14, "1MB" 16, "2MB" 18) 
set grid ytics lc rgb "#bbbbbb"
set terminal postscript eps enhanced color
set output label.'.eps'
set lmargin 20
set rmargin 5
set bmargin 5
set tmargin 5

set border 3


plot "1T" title "One pair" with lp lt rgb "blue" pt 7 ps 1.5 lw 3, "2T" title "Two pairs" with lp lt rgb "red" dashtype 2 pt 5 ps 1.5 lw 3, "4T" title "Four pairs" with lp lt rgb "black" pt 2 ps 1.5 lw 3, "8T" title "Eight pairs" with lp lt rgb "#006400" dashtype 5 pt 11 ps 2 lw 3
