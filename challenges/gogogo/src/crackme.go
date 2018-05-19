package main
import (
    "bufio"
    "fmt"
    "os"
    "encoding/hex"
    "strings"
    "crypto/md5"
)

func bleh(c chan string) {
    reader := bufio.NewReader(os.Stdin)
    text, _ := reader.ReadString('\n')
    c <- text // send sum to c
}

func constr(s []byte, c chan string) {
    a := "Good Bye!"

    if len(s) != 16 {
        c <- a
    }  else {
        var ab [16]byte
        ab[0] = 0xae
        ab[1] = 0x10
        ab[2] = 0x1b
        ab[3] = 0xae
        if s[1]^0x3 != ab[0]{
            c<-a
            return
        }
        if s[0]&0xfe != ab[1]{
            c<-a
            return
        }
        if s[3]|0x3 != ab[2]{
            c<-a
            return
        }
        if s[2]^0xde != ab[3]{
            c<-a
            return
        }
        ab[4] = 0xfa
        ab[5] = 0xfe
        ab[6] = 0x10
        ab[7] = 0xbe

        if s[5]^0xaf != ab[5]{
            c<-a
            return
        }
        if s[7]^0x92 != ab[7]{
            c<-a
            return
        }
        if s[4]|0x3a != ab[4]{
            c<-a
            return
        }
        if s[6]&0x19 != ab[6]{
            c<-a
            return
        }
        
        ab[8] = 33
        ab[9] = 0xad
        ab[10] = 219
        ab[11] = 0xba
        if s[8]|0x3^0xde != ab[8]{
            c<-a
            return
        }
        if s[9]^0xde^0xa1 != ab[9]{
            c<-a
            return
        }
        if s[10]^0x32|0xca&0xbe != ab[10]{
            c<-a
            return
        }
        if s[11]^0x13^s[10] != ab[11]{
            c<-a
            return
        }
        ab[12] = 223
        ab[13] = 0xef
        ab[14] = 0x32
        ab[15] = 0x25
        if s[12]^0x31&0xfa != ab[12]{
            c<-a
            return
        }
        if s[13]^0x3a != ab[13]{
            c<-a
            return
        }
        if s[14]^s[13] != ab[14]{
            c<-a
            return
        }
        if s[15]^s[1]^s[2] != ab[15]{
            c<-a
            return
        }
        hasher := md5.New()
        hasher.Write(s)
        ans := hasher.Sum(nil)
        out := fmt.Sprintf("The flag is CrossCTF{%X}", ans)
        c <- out
    }
}

func conv(s string, c chan []byte) {
    s = strings.TrimSpace(s)
    data, err := hex.DecodeString(s)
    if err != nil {
    }
    c <- data
}

func main() {
    fmt.Println("Welcome to CrossCTF 2018!")
    fmt.Println("Enter the password:")
    c := make(chan string)
    d := make(chan []byte)
    go bleh(c)
    x := <- c
    go conv(x,d)
    bytes := <- d
    e := make(chan string)
    go constr(bytes, e)
    out := <- e
    fmt.Println(out)
}
