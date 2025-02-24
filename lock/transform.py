def transform_char(char, pos):
    val = ord(char)
    # Match assembly operations
    val = (val + pos) & 0xFF              # add al, cl
    val = ~val & 0xFF                     # not al
    val = val ^ 0x44                      # xor al, 0x42
    val = (val + 0x17) & 0xFF            # add al, 0x37
    val = ((val >> 3) | (val << 5)) & 0xFF  # ror al, 1
    val = (val - pos) & 0xFF              # sub al, cl
    return val

# Your flag here
flag = "apoorvctf{w0w_1ts_4m4z1ng_1snt!}"
print(len(flag))

# Transform each character
transformed = []
for i in range(len(flag)):
    transformed.append(transform_char(flag[i], i))

# Print in assembly format
print("expected: db", end=" ")
for i in range(0, len(transformed), 8):
    chunk = transformed[i:i+8]
    line = ", ".join(f"0x{x:02X}" for x in chunk)
    if i > 0:
        print("         db", end=" ")
    print(f"{line}   ; Position {i}-{i+len(chunk)-1}")

# Print in hex format for verification
print("\nHex array for C:")
print(", ".join(f"0x{x:02X}" for x in transformed))

# Generate solver verification
print("\nTest solution:")
def reverse_transform(val, pos):
    val = (val + pos) & 0xFF                # Undo ADD
    val = ((val << 3) | (val >> 5)) & 0xFF  # Undo ROR
    val = (val - 0x17) & 0xFF               # Undo ADD
    val = val ^ 0x44                        # Undo XOR
    val = ~val & 0xFF
    val = (val - pos) & 0xFF                # Undo ADD
    return val

# Verify transformation is reversible
recovered = ""
for i in range(len(transformed)):
    c = chr(reverse_transform(transformed[i], i))
    recovered += c

print(f"Original : {flag}")
print(f"Recovered: {recovered}")
assert flag == recovered, "Transformation is not reversible!"