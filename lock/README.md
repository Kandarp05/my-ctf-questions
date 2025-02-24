1. User needs to give input
2. We apply some set of operations on this input char by char.
3. We check if transformed is equal to a hardcoded values.
4. user sees all the transformed values.
5. reverses all the operations on these hardcoded values.
6. finds the flag.


```
python transform.py
nasm -f bin -o stage2.bin stage2.asm
python hello.py
gcc lock.c
./a.out 
```