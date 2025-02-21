zip -0 -e secret.zip flag.png
bkcrack -C secret.zip -c flag.png -p png.bin
bkcrack -C secret.zip -k 8c609774 bd0984d8 8894348c -D solved/decrypt.zip
