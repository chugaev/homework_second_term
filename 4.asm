ldc 3
st 1
ldc 2
st 2
ldc 208574561
st 4
ld 4
st 8
ldc 1
newPair: st 100
ld 1
st 3
ld 2
ldc 1
add
st 2
ld 2
ld 1
cmp
br stack
isPrime: st 100
ld 1
st 5
ld 4
st 3
check2: ld 5
ld 3
sub
st 3
ld 5
ld 3
cmp
st 7
ld 7
br compare2
st 100; free
ld 5
st 8
jmp newValue
compare2: st 100
ldc -1
ld 7
cmp
br stack2
st 100; free
jmp newValue
stack2: st 100
jmp check2
newValue: ld 1
ldc 1
add
st 1
ldc 2
st 2
ld 1
ld 4
cmp
ldc -1
cmp
br newPair
exit: ld 8
ret
check: ld 2
ld 3
sub
st 3
ld 3
ld 2
cmp
st 7
ld 7
br compare
st 100; free
jmp newValue
compare: st 100
ldc -1
ld 7
cmp
br newPair
jmp stack
stack: st 100
jmp check
