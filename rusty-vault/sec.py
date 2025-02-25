import os
import hashlib
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

def main():
    # Hard-coded values (change these as needed)
    password = "LetMeInOrImTellingMom"  # The password from which the AES key is derived
    flag = "apoorvctf{helllo_its_me_james}"  # The flag plaintext

    # Derive a 16-byte AES key from the SHA-256 hash of the password.
    sha256_hash = hashlib.sha256(password.encode()).digest()
    print(sha256_hash.hex())
    key = sha256_hash[:16]  # AES-128 key

    # Generate a random 16-byte IV.
    iv = os.urandom(16)

    # Encrypt the flag using AES-128-CBC with PKCS7 padding.
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_flag = pad(flag.encode(), AES.block_size)
    ciphertext = cipher.encrypt(padded_flag)

    # Print the generated values in hex format.
    print("Generated AES parameters:")
    print("Key:          ", key.hex())
    print("IV:           ", iv.hex())
    print("Ciphertext:   ", ciphertext.hex())
    print("\nCopy and paste the following snippet into your Rust code:")
    print(f'let key = hex!("{key.hex()}");');
    print(f'let iv = hex!("{iv.hex()}");');
    print(f'let ciphertext = hex!("{ciphertext.hex()}");');

if __name__ == '__main__':
    main()
