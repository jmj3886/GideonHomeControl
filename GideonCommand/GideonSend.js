// serial port initialization:
var SerialPort = require('serialport'); // include the serialport library
var portName = process.argv[2]; // get the port name from the command line
var myPort = new SerialPort(portName, 9600);// open the port
 
// these are the definitions for the serial events:
myPort.on('open', openPort); // called when the serial port opens
 
function openPort() {
  var brightness = 0; // the brightness to send for the LED
  console.log('port open');
  console.log('baud rate: ' + myPort.options.baudRate);
 
  // since you only send data when the port is open, this function
  // is local to the openPort() function:
  function sendData() {
    // convert the value to an ASCII string before sending it:
    myPort.write(brightness.toString());
    console.log('Sending ' + brightness + ' out the serial port');
    // increment brightness by 10 points. Rollover if < 255:
    if (brightness < 255) {
      brightness+= 10;
    } else {
      brightness = 0;
  }
}
 
// set an interval to update the brightness 2 times per second:
setInterval(sendData, 500);
}
