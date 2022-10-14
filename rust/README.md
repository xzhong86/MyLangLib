# Rust language


## Setup Env

### Ubuntu

 - `sudo snap install rustup`, but still need `rustup install stable` (and `rustup default stable`)
 - other commands: `rustup toolchain list`


## Other Target

 - list all targets: `rustup target list`
 - install a target: `rustup target add aarch64-unknown-linux-gnu`
 - install a target: `rustup target add aarch64-unknown-linux-musl` for static link
 - install binutils: `apt install binutils-aarch64-linux-gnu` or install gcc-aarch64-linux-gnu

### Cross compile

Refer to:
 - https://stackoverflow.com/questions/39705213/cross-compiling-rust-from-windows-to-arm-linux
 - see p10-cross-aarch64

