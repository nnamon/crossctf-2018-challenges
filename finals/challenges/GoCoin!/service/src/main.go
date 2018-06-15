// main.go

package main

import (
    "strconv"
    "math"
    "github.com/astaxie/beego"
    "html/template"
    "net/http"
)

func main() {
    beego.Router("/", &mainController{}, "get:Get")
    beego.Router("/deposit", &mainController{}, "get:Deposit")
    beego.Router("/withdraw", &mainController{}, "get:Withdraw")
    beego.Router("/flag", &mainController{}, "get:Flag")
    beego.ErrorHandler("404",page_not_found)
    beego.Run()
}

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

func (this *mainController) Flag() {
    purse := this.GetSession("purse")
    bank := this.GetSession("bank")
    if purse == nil {
        this.SetSession("purse", float64(1))
    }
    if bank == nil {
        this.SetSession("bank", float64(0))
    }

    if purse.(float64) < 1.337 {
        this.TplName = "error.html"
        this.Data["message"] = "Insufficient GoCoin! in purse to buy flag."
        return
    }

    this.SetSession("purse", Round(purse.(float64) - 1.337,0.01))
    this.TplName = "flag.html"
}

func (this *mainController) Withdraw() {
    amount, err := strconv.ParseFloat(this.GetString("amount"), 64)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Invalid value in query string 'amount'."
        return
    }

    purse := this.GetSession("purse")
    bank := this.GetSession("bank")
    if purse == nil {
        this.SetSession("purse", float64(1))
    }
    if bank == nil {
        this.SetSession("bank", float64(0))
    }
    purse = this.GetSession("purse")
    bank = this.GetSession("bank")

    if bank.(float64) >= amount {
        this.SetSession("purse", Round(purse.(float64) + amount,0.01))
        this.SetSession("bank", Round(bank.(float64) - amount,0.01))
    } else {
        this.TplName = "error.html"
        this.Data["message"] = "Insufficient GoCoin! in bank."
        return
    }
    this.Data["purse"] = this.GetSession("purse").(float64)
    this.Data["bank"] = this.GetSession("bank").(float64)
    this.Data["amount"] = amount
    this.TplName = "withdraw.html"
}

func (this *mainController) Deposit() {
    amount, err := strconv.ParseFloat(this.GetString("amount"), 64)
    if err != nil {
        this.TplName = "error.html"
        this.Data["message"] = "Invalid value in query string 'amount'."
        return
    }

    purse := this.GetSession("purse")
    bank := this.GetSession("bank")
    if purse == nil {
        this.SetSession("purse", float64(1))
    }
    if bank == nil {
        this.SetSession("bank", float64(0))
    }
    purse = this.GetSession("purse")
    bank = this.GetSession("bank")

    if purse.(float64) >= amount {
        this.SetSession("purse", Round(purse.(float64) - amount,0.01))
        this.SetSession("bank", Round(bank.(float64) + amount,0.01))
    } else {
        this.TplName = "error.html"
        this.Data["message"] = "Insufficient GoCoin! in purse."
        return
    }
    this.Data["purse"] = this.GetSession("purse").(float64)
    this.Data["bank"] = this.GetSession("bank").(float64)
    this.Data["amount"] = amount
    this.TplName = "deposit.html"
}

func (this *mainController) Get() {
    purse := this.GetSession("purse")
    bank := this.GetSession("bank")
    if purse == nil {
        this.SetSession("purse", float64(1))
    }
    if bank == nil {
        this.SetSession("bank", float64(0))
    }

    this.Data["purse"] = this.GetSession("purse").(float64)
    this.Data["bank"] = this.GetSession("bank").(float64)
    this.TplName = "index.html"
}

