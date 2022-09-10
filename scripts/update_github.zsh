#!/bin/zsh

if (( $# == 0 )); then
    echo "Please provide commit message, e.g. ./update_github.zsh \"add file via upload\""
    exit 1
fi
git add .
git commit -m $1
git push origin development