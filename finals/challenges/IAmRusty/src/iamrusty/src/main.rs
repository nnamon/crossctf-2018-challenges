pub mod lib;

use std::iter::repeat;
use lib::QYEncryption;

struct Input {
    key: &'static str,
    input: &'static str,
    output: &'static [u8]
}

fn main() {
    let t = Input {
        key: "RustyLangIsFun",
        input: "WhatIsTheFlag?",
        output: &[193, 43, 110, 37, 49, 203, 177, 168, 213, 56, 111, 114, 136, 234, 91, 129, 74, 3, 134, 159, 134, 47, 53, 245, 103, 247, 251, 52, 198, 245, 208, 139, 188, 151, 208, 36, 109, 245, 48, 174, 123, 154]
    };
    let mut qyencryption = QYEncryption::new(t.key.as_bytes());
    let mut result2: Vec<u8> = repeat(0).take(t.input.len()).collect();
    qyencryption.encrypt(t.input.as_bytes(), result2.as_mut_slice());
    println!("The encrypted flag is {:?}", result2);
}