BITS 64

check_password:
    call get_ip
get_ip:
    pop rbx
    
    ; Check exactly 32 characters
    xor rcx, rcx
.count_loop:
    cmp rcx, 32        ; Stop if we reach 32
    je .check_null
    mov al, [rdi + rcx]
    test al, al
    jz wrong_pass      ; Too short if we hit null before 32
    inc rcx
    jmp .count_loop
.check_null:
    mov al, [rdi + rcx]  ; Character at position 32
    test al, al
    jnz wrong_pass       ; Too long if not null

    ; Transform and check each character
    xor rcx, rcx        ; Reset counter
.transform_loop:
    movzx rax, byte [rdi + rcx]   ; Get char
    
    ; Apply the exact transformations from transform.py:
    add al, cl                     ; add position (val + pos)
    not al                         ; not val
    xor al, 0x44                   ; XOR with 0x44
    add al, 0x17                   ; add 0x17
    ror al, 3                      ; rotate right by 3
    sub al, cl                     ; sub position (val - pos)
    
    ; Compare with expected value
    lea rdx, [rbx + (expected - get_ip)]
    cmp al, [rdx + rcx]
    jne wrong_pass
    
    inc rcx
    cmp rcx, 32
    jne .transform_loop
    
    ; Success - print flag
    lea rsi, [rbx + (flag - get_ip)]
    mov rdx, flag_len
    jmp print

wrong_pass:
    lea rsi, [rbx + (wrong - get_ip)]
    mov rdx, wrong_len
print:
    mov rax, 1
    mov rdi, 1
    syscall
    ret

align 8
; These values should match output from transform.py for your flag
expected: db 0x3E, 0x3B, 0x3A, 0x19, 0x98, 0xF5, 0x37, 0xF3   ; Position 0-7
         db 0x95, 0xC1, 0x20, 0xE7, 0xDD, 0xD0, 0x65, 0xDA   ; Position 8-15
         db 0xD9, 0x4B, 0x70, 0x37, 0x2D, 0x54, 0x4C, 0x93   ; Position 16-23
         db 0x63, 0x42, 0xC6, 0x6E, 0xED, 0x0B, 0x55, 0xA8   ; Position 24-31

flag: db "Correct Password!!",10,0
flag_len equ $ - flag
wrong: db "Wrong! Try analyzing the transformations.",10,0
wrong_len equ $ - wrong