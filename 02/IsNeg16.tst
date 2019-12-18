load IsNeg16.hdl,
output-file IsNeg16.out,
compare-to IsNeg16.cmp,
output-list in%B2.16.2 out%B2.1.2;

set in %B0000000000000000,
eval,
output;

set in %B0000000000000001,
eval,
output;

set in %B0000000010001000,
eval,
output;

set in %B1000000000000000,
eval,
output;

set in %B1111111111111111,
eval,
output;