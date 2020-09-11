

set boxwidth 0.2

set style fill solid

set term postscript eps font "Times-Roman" enhanced color
set output'test.eps'

plot 'bar_data_0.dat' using 1:2:0 with boxes lc variable