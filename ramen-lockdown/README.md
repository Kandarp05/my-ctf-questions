## Description
A criminal mastermind named larry stole Chef Tataka ultimate ramen recipe and yeeted it into a password-protected zip file. Inside? A sacred text file with the secret to flavor nirvana. Crack the zip, save the slurp. No pressure. 🍜💀

- Author: hampter/kandarp
- flag: apoorvctf{w0rst_r4m3n_3v3r_ong}

## Writeup

So we got a zip file, when you try to extract the zip, it asks for a password.

Next thing to think about is how to recover this password.

Execute `7z l recipe.zip` 
```
7-Zip 24.09 (x64) : Copyright (c) 1999-2024 Igor Pavlov : 2024-11-29
 64-bit locale=C.UTF-8 Threads:12 OPEN_MAX:1024, ASM

Scanning the drive for archives:
1 file, 90008 bytes (88 KiB)

Listing archive: recipe.zip

--
Path = recipe.zip
Type = zip
Physical Size = 90008

   Date      Time    Attr         Size   Compressed  Name
------------------- ----- ------------ ------------  ------------------------
2025-02-24 18:37:30 .....        89796        89808  secret_recipe.png
------------------- ----- ------------ ------------  ------------------------
2025-02-24 18:37:30              89796        89808  1 files
```

Hence there is a secret_recipe.png in out zip file.

Now i started looking for some vulnerability in protected zip.

I found an article mentioning about some known plainext attack in **PKZIP stream cipher**

But for this attack to work we need to knwo some plaintext in the given zip.

**What is one thing present in all png??** -> Magic String of PNG

We know every png starts with 
```
�PNG

IHDR
```

or `89 50 4E 47 0D 0A 1A 0A 00 00 00 0D 49 48 44 52` in hex

lets try using this as our plaintext.

I found a tool called [bkcrack](https://github.com/kimci86/bkcrack)

i used the cmd `bkcrack -C recipe.zip -c secret_recipe.png -p png.bin`

- recipe.zip is the zip file
- secret_recipe.png is the cipher text(Since we know plaintext from png)
- png.bin is the magic string of PNG with IHDR

After running this we get
```
bkcrack 1.7.1 - 2024-12-21
[18:43:49] Z reduction using 9 bytes of known plaintext
100.0 % (9 / 9)
[18:43:49] Attack on 721680 Z values at index 6
Keys: 7cfefd6a 4aedd214 970c7187
41.3 % (297837 / 721680)
Found a solution. Stopping.
You may resume the attack with the option: --continue-attack 297837
[18:47:12] Keys
7cfefd6a 4aedd214 970c7187
```

Horray! We got the internal keys `7cfefd6a 4aedd214 970c7187`

Now we use `bkcrack -C recipe.zip -k 7cfefd6a 4aedd214 970c7187 -D unprotected.zip` (this will make a clone of original zip without password)

Now unzip the new zip `unzip unprotected.zip`
Open secret_recipe.png in any image_viewer to get the flag.
