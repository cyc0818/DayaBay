#!/bin/csh
# arguments are $*
foreach i (37559.csh 38551.csh 39584.csh 21660.csh 22516.csh 23239.csh 24735.csh 26088.csh 34759.csh 35814.csh 36914.csh 37645.csh)
qsub -q dyb64q Script/EH1/run$i
#echo Script/EH1/run$i
end

