import logo from './logo.svg';
import './App.css';
import React, { useState, useEffect, useMemo, useRef } from 'react';

function App() {
 const[port, setPort] =  useState();
 const [bit_val, setBit_val] = useState(49);
 const [readval, setReadVal] = useState("");
 const[led_style, setLedStyle] = useState("");
 const[sensor_data, setSensorData] = useState({"array_1":[], "array_2":[], "array_3":[]});
const[sensor_display, setSensorDisplay] = useState();
const sty = useRef()
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
    const data = new Uint8Array([49,49,49,49,49,49]); // hello
    await writer.write(data);
    
    // Allow the serial port to be closed later.
    writer.releaseLock();
    console.log("writing 1");
  }
  
const off = async()=>{
  let writer = port.writable.getWriter()

  const data = new Uint8Array([48,48,48,48,48,48]); // hello
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
let tempstring = "";
while (true) {
  const { value, done } = await reader.read();
  if (done) {
    // Allow the serial port to be closed later.
    reader.releaseLock();
    break;
  }
  
 //Ravi logic for sensor packet decode
 let packet_array = []
 let super_value = textDecoder.decode(value)
 tempstring+=super_value;
 packet_array = tempstring.split("\r\n");
 tempstring = packet_array[packet_array.length -1];
 packet_array = packet_array.slice(0,packet_array.length -1);
 for(let i =0; i< packet_array.length; i++){
  console.log(packet_array[i]);
 }

 
  if(textDecoder.decode(value) == "1" ){
    if(sty.current.className!="led-blue"){
      sty.current.className = "led-blue"
    }
    
    console.log(sty.current.className)
    }else if(textDecoder.decode(value) == "0"  ){
      if (sty.current.className != "led-off"){
        sty.current.className = "led-off"
      }
      
    }
    
   

    
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

const set_display = () =>{
  //setSensorDisplay("array1: "+ sensor_data['array_1']+ " array_2: "+ sensor_data['array_2']+ " array3: "+ sensor_data['array_3']);
  setSensorDisplay(sensor_data)
}
  
  return (
    <div className="App">
    <button onClick={() => openSerialPort()}> Open Serial Port </button>
    <button onClick={() => flash()}> on </button>
    <button onClick={() => off()}> off </button>
    <button onClick={()=> read()}> read</button>
    <button onClick={()=> toggle_light()}> light toggle</button>
    <button onClick={()=> set_display()}> show current data</button>
    <h1>{sensor_display}</h1>
    <div className="led-box">
    <div ref = {sty}></div>
    <p>Blue LED</p>
  </div>
   
    </div>
  );
}

export default App;
