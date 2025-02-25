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
    println!("-----Welcome to the Vault!-----");
    println!("Enter the secret phrase: ");
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
        let iv = hex!("0810d5b049a023abd5ca5654234c37f7");
        let ciphertext = hex!("61747e192a6e4e3c9a831d0eace1b1c28ba605d0fb070d0061c469a0e912508eb91479f3c4f60c63f64b11a0ce4b4fbc");

        let cipher = Cipher::aes_128_cbc();

        let decrypted_data = decrypt(cipher, &key, Some(&iv), &ciphertext)
            .expect("failed to decrypt data");

        let flag = String::from_utf8(decrypted_data).unwrap();
        println!("Stage 3 passed!!");
        println!("The flag is: {}", flag);
    } else {
        println!("Stage 3 failed!!");
        exit(0);
    }
}