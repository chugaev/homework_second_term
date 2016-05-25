ldc 1
st 0
ldc 3
ldc 3
st 1
st 3
ldc 1
st 2
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
st 6
ldc 1
ld 0
add
st 0
ld 0
ldc 10001
cmp
br newValue
st 100
ld 6
ret
newValue: ld 1
ldc 2
add
st 1
ldc 2
st 2
ld 1
st 3
check:
ld 2
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
st 100; free
jmp check
stack: st 100
jmp check
