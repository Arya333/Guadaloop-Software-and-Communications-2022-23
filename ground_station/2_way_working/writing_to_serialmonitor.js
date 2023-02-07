// import serial port as a constant
const { SerialPort } = require('serialport')

// Create a port
const port = new SerialPort({
  path: '/dev/tty.usbmodem1101',
  baudRate: 9600,
})

// write and just check for error
port.write('main screen turn on', function(err) {
  if (err) {
    return console.log('Error on write: ', err.message)
  }
  console.log('message written')
})

// Open errors will be emitted as an error event
port.on('error', function(err) {
  console.log('Error: ', err.message)
})