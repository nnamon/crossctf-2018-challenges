var flag = require("./flag.js");
var express = require('express')
var app = express()

app.get('/flag', function (req, res) {
    if (req.query.third) {
        if (Array.isArray(req.query.third)) {
            third = req.query.third;
            third_sorted = req.query.third.sort();
            if (Number.parseInt(third[0]) > Number.parseInt(third[1]) && third_sorted[0] == third[0] && third_sorted[1] == third[1]) {
                res.send(flag.flag);
                return;
            }
        }
    }
    res.send("Try to solve this.");
});

app.listen(31337)
