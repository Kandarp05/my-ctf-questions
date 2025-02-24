# encrypt.py
key = 0xAA
with open("stage2.bin", "rb") as f:
    data = bytearray(f.read())

encrypted = bytearray(b ^ key for b in data)
before = bytearray(b ^ key for b in encrypted)

# Print out the encrypted bytes in C array format.
print(", ".join("0x{:02X}".format(b) for b in encrypted))
print()
print(" ".join("{:02X}".format(b) for b in before))


