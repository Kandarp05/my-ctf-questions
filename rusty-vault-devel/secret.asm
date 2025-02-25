; flag.asm - Flat binary containing the flag
; Assemble with: nasm -f bin flag.asm -o flag_asm.bin

BITS 16
    db "apoorvctf{helllo_its_me_james}", 0
