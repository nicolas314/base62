package main

import (
    "fmt"
    "os"
    "strconv"
    "strings"
)

const (
    b62_digits =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
)

func b62_encode(num uint64) string {
    var rem uint64
    s:=""
    for num>0 {
        rem = num % 62 ;
        s=string(b62_digits[rem])+s
        num = num / 62
    }
    return s
}

func b62_decode(s string) uint64 {
    var (
        num uint64
        pow uint64
    )
    pow=1
    for i:=len(s)-1 ; i>=0 ; i-- {
        num += pow * uint64(strings.Index(b62_digits, string(s[i])))
        pow *= 62
    }
    return num
}

func main() {
    if len(os.Args)<2 {
        fmt.Printf("use: %s NUM\n", os.Args[0])
        return
    }
    val, _ := strconv.ParseUint(os.Args[1], 10, 64)
    enc := b62_encode(val)
    fmt.Printf("b62[%s]\n", enc)
    dec := b62_decode(enc)
    fmt.Printf("-> %v\n", dec)
}

