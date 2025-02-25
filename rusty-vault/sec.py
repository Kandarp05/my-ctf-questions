# encrypt.py
with open("secret.bin", "rb") as f:
    data = bytearray(f.read())

# XOR encrypt with 0xF9
encrypted = [b ^ 0xF9 for b in data]

# Print out the encrypted bytes in Rust array format
print(", ".join("0x{:02X}".format(b) for b in encrypted))

