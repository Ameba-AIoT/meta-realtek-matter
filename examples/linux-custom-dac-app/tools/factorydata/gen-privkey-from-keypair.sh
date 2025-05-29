#!/usr/bin/env bash

# extract privkey from keypair
openssl ec -text -noout -in "$1" | sed '0,/priv:$/d' | sed '/pub:/,$d' | sed 's/://g' | tr -d "[:space:]" | xxd -r -p > "$2"

# print the privkey
xxd -p "$2" | sed 's/../0x&, /g'
