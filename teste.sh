#!/bin/bash
#Script que realiza 5 execuções para cada instancia

for INST in 138.nsp 507.nsp 849.nsp 365.nsp 869.nsp 749.nsp 505.nsp 512.nsp 494.nsp 25.nsp 144.nsp 646.nsp 418.nsp 298.nsp 439.nsp 302.nsp 290.nsp 798.nsp 665.nsp 906.nsp 58.nsp 177.nsp 229.nsp 441.nsp 710.nsp 593.nsp 832.nsp 340.nsp 818.nsp 575.nsp 946.nsp 681.nsp 232.nsp
do
   echo "Executado testes para instancia $INST"
   for X in 1 2 3 4 5
   do
      #O comando abaixo será executado 5 vezes
      #A pasta das instâncias está certa?
      ./tcc instancias/$INST 423
   done
done
