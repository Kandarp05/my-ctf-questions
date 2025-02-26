# Antihash

## Concept

The task is to reverse-engineer a compiled program and work out its input from a given output. This requires basic skills of this field, e.g. decompiling a binary, analysing its content and reversing the steps of the algorithm to transform its output back into the input. Alternatively, some observation skills allow for a blackbox solution.

The given binary is an ELF executable of a program written in C, compiled with `gcc -Og challenge.c` on and `gcc` version 11.4.0.

## Writeup

There are two ways to solve this challenge. The first is by decompiling the binary, understanding the algorithm and reversing its steps to reconstruct the flag out of the given output.

When looking at the decompiled code, one notices that the `main` function handles in- and output (output bytes are represented as octal) and calls a function called `logic`. This contains the algorithm's logic.

In that function, odd input lengths are transformed into inputs of even length, after which three functions are called in a row: `substitute`, `shuffle` and `inflate`.

`substitute` runs each byte through a hardcoded substitution lookup table. This can be reversed by taking the table and computing the inverse mapping.

`shuffle` takes every second character beginning from the start of the input and swaps it with every second character beginning from the end of the input respectively. Since it is only swaps, this can be reversed by doing the same operations again.

`inflate` takes every second character and appends its xor with 20 to the end of the input. One can therefore simply discard the last third of the output.

Putting everything together as in [this script](reversed.py), the flag can be obtained.

Alternatively, diving deeper into the algorithm can be avoided in this case, since a blackbox-reversing approach is possible. With careful observation of different inputs and their corresponding outputs, one can learn that output lengths are deterministically corresponding to input lengths and that each byte of the output corresponds to only one byte of the input.

Therefore, it is possible to test different input lengths to find the length of the output that matches the length of the flag output. Then, by changing only one byte at a time, a mapping between input and output byte can be obtained. Finally, the flag can be recovered by looping through all possible values for each input byte at a time and observing if the output bytes in the mapping match the output bytes of the flag at those positions. An example script of this approach can be found [here](blackbox.py).
