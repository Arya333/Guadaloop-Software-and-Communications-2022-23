import logo from './logo.svg';
import './App.css';
import React, { useState, useEffect } from 'react';
function App() {
 console.log("dom fire")
 const[port, setPort] =  useState();

 const [bit_val, setBit_val] = useState(49);


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
  
  // if (writer['desiredSize'] != undefined){
  //   console.log("writer is: "+ writer['desiredSize'])
  const data = new Uint8Array([48]); // hello
  await writer.write(data);

  // if ( bit_val == 48){
  //   setBit_val(49)
  // }else {
  //   setBit_val(48)
  // }
  // Allow the serial port to be closed later.
  writer.releaseLock();
}
    
  
  return (
    <div className="App">
    <button onClick={() => openSerialPort()}> Open Serial Port </button>
    <button onClick={() => flash()}> on </button>
    <button onClick={() => off()}> off </button>
    </div>
  );
}

export default App;
