var flag = require("./flag.js");
var express = require('express')
var app = express()

app.get('/flag', function (req, res) {
    var re = new RegExp('^I_AM_ELEET_HAX0R$', 'g');
    if (re.test(req.query.fifth)) {
        if (req.query.fifth === req.query.six && !re.test(req.query.six)) {
            res.send(flag.flag);
        }
    }
    res.send("Try to solve this.");
});

app.listen(31337)
