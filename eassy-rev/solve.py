subs = "0123456789abcdefghijklmnopqrstuvwxyz_{}"
shift = 7
garbage_chars = "!@#$%^&*()"
xor_key = 0xFF

def reverse_transform(text):
    transformed = [ord(c) for c in text]
    not_bytes = [b ^ xor_key for b in transformed]
    flag_bytes = [~b & 0xFF for b in not_bytes]
    flag = ''.join(chr(b) for b in flag_bytes)
    
    flag = flag[::-1]
    
    clean = ""
    for i in range(0, len(flag)):
        if (i - 1) % 4 != 0:
            clean += flag[i]
            
    result = ""
    for c in clean:
        if c in subs:
            idx = subs.index(c)
            result += subs[(idx - shift) % len(subs)]
        else:
            result += c
            
    return result

if __name__ == "__main__":
    encrypted = "6!!sbn*ass%84z@84c(8o_^4#_#8b0)5m_&j}y$vvw!h"
    flag = reverse_transform(encrypted)
    print(flag)
