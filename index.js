var SerialPort = require('serialport');
var serialport = new SerialPort('COM4', {
    baudRate: 9600
});
serialport.open((err) => {
    if (err) {
        return console.log(err);
    }
})

serialport.on('data', (data) => {
    console.log(data.toString());
})