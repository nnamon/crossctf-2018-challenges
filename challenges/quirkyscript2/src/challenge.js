var flag = require("./flag.js");
var express = require('express')
var app = express()

app.get('/flag', function (req, res) {
    if (req.query.second) {
        if (req.query.second != "1" && req.query.second.length == 10 && req.query.second == true) {
            res.send(flag.flag);
            return;
        }
    }
    res.send("Try to solve this.");
});

app.listen(31337)
