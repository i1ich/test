var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var Names = [];
var colors = ["red", "white"];
var turn = 1;
var game = 1;
var CellNum;

const port = process.env.PORT || 3000;
app.get('/', function (req, res) {
    res.sendFile(__dirname + '/index.html');
});


io.on('connection', function (socket) {

    socket.on('shoot', function (msg) {
        io.emit('shoot', msg);
    });
    socket.on('n_user', function (msg) {
        Names.push(msg);
        io.emit('n_user', msg + "," + String(Names.length - 1));
    });
    socket.on('turn1', function (msg) {
        game = 1;
        CellNum = msg.split(",");
        if (CellNum[1] == turn) {
            console.log(msg + ',' + colors[turn]);
            io.emit('turn1', (msg + "," + colors[turn]));
            turn = (turn + 1) % 2;
        }

    });
    socket.on('debug', function (msg) {
        io.emit('debug', msg);
    });
    socket.on('win', function (msg) {
        if (game != 0)
            io.emit('win', msg);
        game = 0;
    });
});

http.listen(port, function () {
    console.log('listening on *:3000');
});
