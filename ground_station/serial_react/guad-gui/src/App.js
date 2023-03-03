import logo from './logo.svg';
import './App.css';
import React, { useState, useEffect, useMemo } from 'react';

function App() {
 const[port, setPort] =  useState();
 const [bit_val, setBit_val] = useState(49);
 const [readval, setReadVal] = useState("");
 const[led_style, setLedStyle] = useState("led-off");


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
    
    // Allow the serial port to be closed later.
    writer.releaseLock();
    console.log("writing 1");
  }
  
const off = async()=>{
  let writer = port.writable.getWriter()

  const data = new Uint8Array([48]); // hello
  await writer.write(data);
  console.log("writing 0");
 
  // Allow the serial port to be closed later.
  writer.releaseLock();
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
 
  if(textDecoder.decode(value) ==1){
    setLedStyle("led-blue")
    }else if(textDecoder.decode(value) ==0){
      setLedStyle("led-off")
    }
    setReadVal(textDecoder.decode(value));
    //console.log(textDecoder.decode(value));
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
    <div className="led-box">
    <div className={led_style}></div>
    <p>Blue LED</p>
  </div>
   
    </div>
  );
}

export default App;
