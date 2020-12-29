set tics font ",17"
set key right top Left box 3
set key font ",21" height 1. width 1.7 spacing 1.7

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
set tmargin 2

set border 3
plot "BoringSSL" title "BoringSSL" with lp lt rgb "blue" pt 7 ps 1.5 lw 3, "Libsodium" title "Libsodium" with lp lt rgb "red" dashtype 2 pt 5 ps 1.5 lw 3, "CryptoPP" title "CryptoPP" with lp lt rgb "black" pt 2 ps 1.5 lw 3


