var flag = require("./flag.js");
var express = require('express')
var app = express()

app.get('/flag', function (req, res) {
    if (req.query.first) {
        if (req.query.first.length == 8 && req.query.first == ",,,,,,," ) {
            res.send(flag.flag);
            return;
        }
    }
    res.send("Try to solve this.");
});

app.listen(31337)
