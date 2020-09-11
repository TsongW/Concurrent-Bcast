
set style data histograms
set boxwidth 0.2

set term postscript eps font "Times-Roman" enhanced color
set output'test.eps'

plot "bar_data_4.dat" using 2:xtic(1) title "Default" lt rgb "#406090", "" using 3 title "My Own" lt rgb "#40FF00"