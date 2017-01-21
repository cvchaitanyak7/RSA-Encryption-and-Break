#!/bin/csh
set user = $1
set Expected = HelloFrom.vchekuri3.frJMHSKtOfoBLVekrmNyahMItYibhJgoPlBKOstp
set Actual = `./BreakRSA  4300323742938198823 3495556278332104687  1646884497544512787 3516850373166194470 880905397825181659 262636296119318152 3128822541910951002 2559157359592463524 1449138222836340065 2103087374889542074 2076621050138228374 868326756664828182`
echo "expected is $Expected" 
echo "actal    is $Actual"
if ( "$Expected" == "$Actual" ) then
echo "Grade for user $user is 100"
else
echo "Grade for user $user is 50"
endif
