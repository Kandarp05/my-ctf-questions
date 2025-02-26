subs = "0123456789abcdefghijklmnopqrstuvwxyz_{}"
shift = 7
garbage_chars = "!@#$%^&*()"
xor_key = 0xFF

def inflate(text):
    result = ""
    for i, c in enumerate(text):
        result += c
        if i % 3 == 0:
            result += garbage_chars[i % len(garbage_chars)]
    return result

flag = "apoorvctf{w41t#_th15_1s_1ll3g4l!}"

result = ""
for c in flag:
    if c in subs:
        idx = subs.index(c)
        result += subs[(idx + shift) % len(subs)]
    else:
        result += c
flag = result

flag = inflate(flag)
flag = flag[::-1]
flag_bytes = flag.encode('utf-8')
not_bytes = bytes((~b & 0xFF) for b in flag_bytes)
transformed = bytes(b ^ xor_key for b in not_bytes)

print(''.join(chr(x) for x in transformed))


