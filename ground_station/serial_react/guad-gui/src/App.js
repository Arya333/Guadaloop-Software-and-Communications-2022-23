import logo from './logo.svg';
import './App.css';
import React, { useState, useEffect } from 'react';

function App() {
 console.log("dom fire")
 const[port, setPort] =  useState();

 const [bit_val, setBit_val] = useState(49);
 const [readval, setReadVal] = useState("");

  const openSerialPort = async () =>{
   
   const temp_port = await navigator.serial.requestPort();
      await temp_port.open({
        baudRate: 115200
      });
      setPort(temp_port);
      
  }

  const flash = async() => {
   let writer = port.writable.getWriter()
    
    // if (writer['desiredSize'] != undefined){
    //   console.log("writer is: "+ writer['desiredSize'])
    const data = new Uint8Array([49]); // hello
    await writer.write(data);

    // if ( bit_val == 48){
    //   setBit_val(49)
    // }else {
    //   setBit_val(48)
    // }
    // Allow the serial port to be closed later.
    writer.releaseLock();
  }
  
const off = async()=>{
  let writer = port.writable.getWriter()

  const data = new Uint8Array([48]); // hello
  await writer.write(data);
  // Allow the serial port to be closed later.
  writer.releaseLock();
}
function delay(time) {
  return new Promise(resolve => setTimeout(resolve, time));
}
const read =async() =>{
// Listen to data coming from the serial device.
const textDecoder = new TextDecoder();
// Listen to data coming from the serial device.
const reader = port.readable.getReader();
while (true) {
  const { value, done } = await reader.read();
  if (done) {
    // Allow the serial port to be closed later.
    reader.releaseLock();
    break;
  }
  // value is a Uint8Array.
 
 
    setBit_val(textDecoder.decode(value))
    console.log(textDecoder.decode(value));

    // await delay(1000);
}
}
const toggle_light = async() => {
  let writer = port.writable.getWriter()
  
  
  const data = new Uint8Array([bit_val]); // hello
  await writer.write(data);

 
  // Allow the serial port to be closed later.
  writer.releaseLock();
  if ( bit_val == 48){
    setBit_val(49)
  }else {
    setBit_val(48)
  }
}
  
  return (
    <div className="App">
    <button onClick={() => openSerialPort()}> Open Serial Port </button>
    <button onClick={() => flash()}> on </button>
    <button onClick={() => off()}> off </button>
    <button onClick={()=> read()}> read</button>
    <button onClick={()=> toggle_light()}> light toggle</button>
    <h1>{bit_val}</h1>

    <h2>{readval}</h2>
    </div>
  );
}

export default App;
