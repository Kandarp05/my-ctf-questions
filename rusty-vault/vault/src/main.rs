use std::{io::{self, Write}, process::exit};
const PROC: &[u8] = &[0x98, 0x89, 0x96, 0x96, 0x8B, 0x8F, 0x9A, 0x8D, 0x9F, 0x82, 0x91, 0x9C, 0x95, 0x95, 0x95, 0x96, 0xA6, 0x90, 0x8D, 0x8A, 0xA6, 0x94, 0x9C, 0xA6, 0x93, 0x98, 0x94, 0x9C, 0x8A, 0x84, 0xF9];

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

fn decrypt_xor(data: &[u8], key: u8) -> Vec<u8> {
    data.iter().map(|&byte| byte ^ key).collect()
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

    // let mut is_stage_1 = false;

    // let len = password.len();
    // if len <= 16 {
    //     println!("Stage 1 failed!!");
    //     exit(0);
    // }

    // is_stage_1 = check_stage_1(&password, is_stage_1);
    // if !is_stage_1 {
    //     println!("Stage 1 failed!!");
    //     exit(0);
    // }

    // let mut is_stage_2 = false;
    // if len > 16 {
    //     println!("Stage 2 failed!!");
    //     exit(0);
    // }

    // is_stage_2 = check_stage_2(&password, is_stage_2);
    // if !is_stage_2 {
    //     println!("Stage 2 failed!!");
    //     exit(0);
    // }

    if password == "hello" {
        println!("Vault open! Here is your treasure");
        // Decrypt the bytes first using XOR with 0xF9
        let decrypted = decrypt_xor(&PROC[..PROC.len()-1], 0xF9);
        match std::str::from_utf8(&decrypted) {
            Ok(flag_str) => println!("Flag: {}", flag_str),
            Err(_) => println!("Failed to convert flag bytes to string"),
        }
    }
}

 98 89 96 96 8b 8f 9a 8d 9f 82 91 9c 95 95 95 96 a6 90 8d 8a a6 94 9c a6 93 98 94 9c 8a 84 f9
