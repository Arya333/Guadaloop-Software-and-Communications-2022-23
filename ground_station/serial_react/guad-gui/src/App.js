import logo from './logo.svg';
import './App.css';
import React, { useState } from 'react';
function App() {
 let port = ''
 let writer = ''
 const [bit_val, setBit_val] = useState(49);
  const openSerialPort = async () =>{
   
    port = await navigator.serial.requestPort();
      await port.open({
        baudRate: 115200
      });
      const writer = port.writable.getWriter();
      writer.releaseLock();
  }

  const flash = async() => {
    // console.log(writer)
  
     writer = port.writable.getWriter();
    const data = new Uint8Array([bit_val]); // hello
    if ( bit_val == 48){
      setBit_val(49)
    }else {
      setBit_val(48)
    }
    
    await writer.write(data);
    console.log("writing")
    // Allow the serial port to be closed later.
    writer.releaseLock();
  }

    
  
  return (
    <div className="App">
    <button onClick={() => openSerialPort()}> Open Serial Port </button>
    <button onClick={() => flash()}> flashy </button>
    </div>
  );
}

export default App;
