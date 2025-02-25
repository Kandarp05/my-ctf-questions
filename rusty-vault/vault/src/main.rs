use std::{io::{self, Write}, process::exit};
use sha2::{Sha256, Digest};
use hex_literal::hex;
use openssl::symm::{decrypt, Cipher};

fn check_stage_1(password: &str, is_stage_1: bool) -> bool{
    let mut is_stage_1 = is_stage_1;
    
    let has_digit = password.chars().any(|c| c.is_ascii_digit());
    let has_lowecase = password.chars().any(|c| c.is_lowercase());

    if !has_digit {
        is_stage_1 = true;
    }

    if has_lowecase {
        is_stage_1 = false;
    }

    is_stage_1
}

fn check_stage_2(password: &str, is_stage_1: bool) -> bool{
    let mut is_stage_1 = is_stage_1;
    
    let has_digit = password.chars().any(|c| c.is_ascii_digit());
    let has_special = password.chars().any(|c| !c.is_alphanumeric());
    
    if has_digit {
        is_stage_1 = true;
    }

    if has_special {
        is_stage_1 = false;
    }

    is_stage_1
}

fn main() {
    println!("Welcome to the Vault!");
    println!("Enter the secret password: ");
    io::stdout().flush().unwrap();

    let mut password = String::new();
    io::stdin()
        .read_line(&mut password)
        .expect("Failed to read input");

    let password = password.trim();

    let mut is_stage_1 = false;

    let len = password.len();
    if len <= 16 {
        println!("Stage 1 failed!!");
        exit(0);
    }

    is_stage_1 = check_stage_1(&password, is_stage_1);
    if !is_stage_1 {
        println!("Stage 1 failed!!");
        exit(0);
    }

    let mut is_stage_2 = false;
    if len > 16 {
        println!("Stage 2 failed!!");
        exit(0);
    }

    is_stage_2 = check_stage_2(&password, is_stage_2);
    if !is_stage_2 {
        println!("Stage 2 failed!!");
        exit(0);
    }

    let mut hasher = Sha256::new();
    hasher.update(password.as_bytes());
    let hash = hasher.finalize();

    let expected_hash = hex!("926fdd45c2c66b215015e3e2496af99bd0d311359757258e70443f8d98bd348e");

    if hash.as_slice() == expected_hash {
        let key = hex!("926fdd45c2c66b215015e3e2496af99b");
        let iv = hex!("e62ce43b30939c8041c898b783731957");
        let ciphertext = hex!("d34516e68ad78f29792f5ac31ea5858dae598e368d17d0fa5a81ee6e61115a83");

        let cipher = Cipher::aes_128_cbc();

        let decrypted_data = decrypt(cipher, &key, Some(&iv), &ciphertext)
            .expect("msg");

        let flag = String::from_utf8(decrypted_data).unwrap();
        println!("Stage 3 passed!!");
        println!("The flag is: {}", flag);
    } else {
        println!("Stage 3 failed!!");
        exit(0);
    }
}