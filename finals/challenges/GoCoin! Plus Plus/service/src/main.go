// main.go

package main

import (
    "strconv"
    "math"
    "github.com/astaxie/beego"
    "html/template"
    "io/ioutil"
    "net/http"
    "github.com/dgrijalva/jwt-go"
    "math/rand"
)

func main() {
    beego.SetStaticPath("/static","static")
    beego.Router("/", &mainController{}, "get:Get")
    beego.Router("/deposit", &mainController{}, "get:Deposit")
    beego.Router("/withdraw", &mainController{}, "get:Withdraw")
    beego.Router("/source", &mainController{}, "get:Source")
    beego.Router("/flag", &mainController{}, "get:Flag")
    beego.ErrorHandler("404",page_not_found)
    beego.Run()
}

var (
    source, _ = ioutil.ReadFile("main.go")
    privateKey, _ = ioutil.ReadFile("keys.rsa")
    publicKey, _ = ioutil.ReadFile("keys.rsa.pub")
)

// This is the controller that this application uses
type mainController struct {
    beego.Controller
}

func Round(x, unit float64) float64 {
    return math.Round(x/unit) * unit
}

func page_not_found(rw http.ResponseWriter, r *http.Request){
    t,_:= template.ParseFiles(beego.BConfig.WebConfig.ViewsPath +"/error.html")
    data :=make(map[string]interface{})
    data["message"] = "Page not found!"
    t.Execute(rw, data)
}
func (this *mainController) Source() {
    this.TplName = "source.html"
    this.Data["message"] = template.HTML(string(source))
}

func (this *mainController) Flag() {
    walletString := this.Ctx.GetCookie("wallet")
    if walletString == "" {
        walletString, err := GenerateNewWallet()
        if err != nil {
            this.TplName = "error.html"
            this.Data["message"] = "Something Went Wrong."
            return
        }
        this.Ctx.SetCookie("wallet", walletString)
    }
    wallet, bank, err := ParseWallet(walletString, publicKey)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Die Hax0r!!! My Crypto is the most secure eva!"
        return
    }

    if wallet < 1337 {
        this.TplName = "error.html"
        this.Data["message"] = "Insufficient GoCoin! in wallet to buy flag."
        return
    }

    wallet = wallet - 1337
    wallet = Round(wallet, 0.01)

    walletString, err = Wallet(wallet, bank, privateKey)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Something Went Wrong."
        return
    }
    this.Ctx.SetCookie("wallet", walletString)
    this.TplName = "flag.html"
}

func (this *mainController) Withdraw() {
    amount, err := strconv.ParseFloat(this.GetString("amount"), 64)
    if err != nil || amount < 0 {
        this.TplName = "error.html"
        this.Data["message"] = "Invalid value in query string 'amount'."
        return
    }

        walletString := this.Ctx.GetCookie("wallet")
    if walletString == "" {
        walletString, err := GenerateNewWallet()
        if err != nil {
            this.TplName = "error.html"
            this.Data["message"] = "Something Went Wrong."
            return
        }
        this.Ctx.SetCookie("wallet", walletString)
    }
    wallet, bank, err := ParseWallet(walletString, publicKey)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Die Hax0r!!! My Crypto is the most secure eva!"
        return
    }


    amount = Round(amount, 0.01)
    if bank >= amount {
        wallet = wallet + amount
        wallet = Round(wallet, 0.01)
        bank = bank - amount
        bank = Round(bank, 0.01)
    } else {
        this.TplName = "error.html"
        this.Data["message"] = "Insufficient GoCoin! in wallet."
        return
    }
    walletString, err = Wallet(wallet, bank, privateKey)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Something Went Wrong."
        return
    }
    this.Ctx.SetCookie("wallet", walletString)
    this.Data["wallet"] = wallet
    this.Data["bank"] = bank
    this.Data["amount"] = amount
    this.TplName = "withdraw.html"
}

func (this *mainController) Deposit() {
    amount, err := strconv.ParseFloat(this.GetString("amount"), 64)
    if err != nil || amount < 0 {
        this.TplName = "error.html"
        this.Data["message"] = "Invalid value in query string 'amount'."
        return
    }

    walletString := this.Ctx.GetCookie("wallet")
    if walletString == "" {
        walletString, err := GenerateNewWallet()
        if err != nil {
            this.TplName = "error.html"
            this.Data["message"] = "Something Went Wrong."
            return
        }
        this.Ctx.SetCookie("wallet", walletString)
    }
    wallet, bank, err := ParseWallet(walletString, publicKey)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Die Hax0r!!! My Crypto is the most secure eva!"
        return
    }
    amount = Round(amount,0.01)
    if wallet >= amount {
        wallet = wallet - amount
        wallet = Round(wallet, 0.01)
        bank = bank + amount
        bank = Round(bank, 0.01)
    } else {
        this.TplName = "error.html"
        this.Data["message"] = "Insufficient GoCoin! in wallet."
        return
    }
    walletString, err = Wallet(wallet, bank, privateKey)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Something Went Wrong."
        return
    }
    this.Ctx.SetCookie("wallet", walletString)
    this.Data["wallet"] = wallet
    this.Data["bank"] = bank
    this.Data["amount"] = amount
    this.TplName = "deposit.html"
}

func Wallet(wallet float64, bank float64, mySigningKey []byte) (string, error) {
    token := jwt.New(jwt.GetSigningMethod("RS256"))
    claims := make(jwt.MapClaims)
    claims["wallet"] = wallet
    claims["bank"] = bank
    claims["rand"] = rand.Uint64()
    token.Claims = claims
    key, err := jwt.ParseRSAPrivateKeyFromPEM(mySigningKey)
    tokenString, err := token.SignedString(key)
    return tokenString, err
}

func ParseWallet(myToken string, myKey []byte) (float64, float64, error) {
    token, err := jwt.Parse(myToken, func(token *jwt.Token) (interface{}, error) {
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            key, err := jwt.ParseRSAPublicKeyFromPEM(myKey)
            return key, err
        }
        return myKey, nil
    })
    if err == nil && token.Valid {
        claims := token.Claims.(jwt.MapClaims)
        wallet, ok := claims["wallet"].(float64)
        if !ok {
            return 0, 0, err
        }
        bank, ok := claims["bank"].(float64)
        if !ok {
            return 0, 0, err
        }
        return wallet, bank, err
    } else {
        return 0, 0, err
    }
}

func GenerateNewWallet() (string, error) {
    walletString, err := Wallet(10, 0, privateKey)
    return walletString, err
}

func (this *mainController) Get() {
    walletString := this.Ctx.GetCookie("wallet")
    if walletString == "" {
        walletString, err := GenerateNewWallet()
        if err != nil {
            this.TplName = "error.html"
            this.Data["message"] = "Something Went Wrong."
            return
        }
        this.Ctx.SetCookie("wallet", walletString)
    }
    wallet, bank, err := ParseWallet(walletString, publicKey)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Die Hax0r!!! My Crypto is the most secure eva!"
        return
    }

    this.Data["wallet"] = wallet
    this.Data["bank"] = bank
    this.TplName = "index.html"
}

