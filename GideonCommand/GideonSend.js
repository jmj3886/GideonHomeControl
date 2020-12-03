// SERIAL PORT INITIALIZATION:
var serialPort = require('serialport'); // SERIAL PORT LIBRARY
var portName = process.argv[2]; // SPECIFY PORTNAME FROM CMD ARGUMENT
var commPort = new SerialPort(portName, 9600, openPort); // CREATES NEW SERIAL PORT

commPort.on('data', dataReceived) // CALLS dataReceived WHEN DATA IS AVAILABLE

function openPort()
{
    console.log('Serial Port \''+portName+'\' Connected');
    console.log('\tBaudRate: ' + commPort.options.baudRate);
}

function dataReceived(data)
{
    console.log('Serial Message Received: ', data);
}

function sendCommMessage(command, protocol, messageLength, message, optional_message)
    {
        if(commPort.isOpen())
        {
            commPort.write(command);
            commPort.write(protocol);
            if(command == "SEND")
            {
                commPort.write(messageLength);
                for(let messagePart of message)
                {
                    commPort.write(messagePart);
                }
                commPort.write(optional_message);
            }
        }
        else
        {
            console.log('Serial Port \''+portName+'\' Not Yet Connected');
        }
  }


//GIDEON COMMAND INITIALIZATION
var christmasModeToggle = False;

function christmasModeOn()
{
    sendCommMessage("SEND", "RF", "1", ["13340"], "5"); // MAIN TREE ON
    christmasModeToggle = True;
}

function christmasModeOff()
{
    sendCommMessage("SEND", "RF", "1", ["13340"], "5"); // MAIN TREE OFF
    christmasModeToggle = False;
}


//HTTP SERVER INITIALIZATION:
var http = require('http'); // HTTP LIBRARY
const host = 'localhost';
const port = 8000;

const requestListener = function (req, res) {
    res.setHeader("Content-Type", "application/json");
    switch (req.url) {
        case "/christmasmode":
            if(christmasModeToggle == True)
            {
                christmasModeOff();
            }
            else
            {
                christmasModeOn();
            }
            break;
    }
}

const server = http.createServer(requestListener);
server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}`);
});


//TIMER INITIALIZATION
var schedule = require('node-schedule'); // SCHEDULER LIBRARY
 
var christmasTimerOn = schedule.scheduleJob('30 15 * * *', christmasModeOn);
var christmasTimerOff = schedule.scheduleJob('0 23 * * *', christmasModeOff);
