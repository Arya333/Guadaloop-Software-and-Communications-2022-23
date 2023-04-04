import logo from './logo.svg';
import './App.css';
import React, { useState, useEffect, useMemo, useRef } from 'react';
import SemiCircleProgressBar from "react-progressbar-semicircle";
import LiveGraph from './components/LiveGraph';
// import { Card, CardContent, Typography, Grid } from '@material-ui';

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

const styles = {
  card: {
    minWidth: 275,
    margin: '10px',
  },
  title: {
    fontSize: 14,
  },
  pos: {
    marginBottom: 12,
  },
};





const sensors = [
  { name: 'Sensor 1', data: '123' },
  { name: 'Sensor 2', data: '456' },
  { name: 'Sensor 3', data: '789' },
  { name: 'Sensor 4', data: '012' },
  { name: 'Sensor 5', data: '345' },
  { name: 'Sensor 6', data: '678' },
  { name: 'Sensor 7', data: '901' },
  { name: 'Sensor 8', data: '234' },
  { name: 'Sensor 9', data: '567' },
  { name: 'Sensor 10', data: '890' },
  { name: 'Sensor 11', data: '123' },
  { name: 'Sensor 12', data: '456' },
];

  
  return (
    <div className="App">
    <button onClick={() => openSerialPort()}> Open Serial Port </button>
    <button onClick={() => flash()}> on </button>
    <button onClick={() => off()}> off </button>
    <button onClick={()=> read()}> read</button>
    <button onClick={()=> toggle_light()}> light toggle</button>
    <button onClick={()=> set_display()}> show current data</button>
    {/* <h1>{sensor_display}</h1>
    <div className="led-box">  </div>
    <div ref = {sty}></div> */}
    
    {/* <div className='progBarContainer'>
    <div className="semicircle-container" style={{position: "absolute"}}><svg width="150" height="75" style={{transform: "rotateY(180deg)", overflow: "hidden"}}><circle cx="75" cy="75" r="70" fill="none" stroke="#202226" strokeWidth="5" strokeDasharray="219.9114857512855" style={{strokeDashoffset: "219.911"}}></circle><circle cx="75" cy="75" r="70" fill="none" stroke="#02B732" strokeWidth="5" strokeDasharray="200.9114857512855" style={{strokeDashoffset: "150", transition: "stroke-dashoffset 0.3s ease 0s, stroke-dasharray 0.3s ease 0s, stroke 0.3s ease 0s;"}}></circle>
    <circle cx="75" cy="75" r="70" fill="none" stroke="#E0B037" strokeWidth="5" strokeDasharray="219.9114857512855" style={{strokeDashoffset: "360", transition: "stroke-dashoffset 0.3s ease 0s, stroke-dasharray 0.3s ease 0s, stroke 0.3s ease 0s;"}}></circle>
    <circle cx="75" cy="75" r="70" fill="none" stroke="#AC2838" strokeWidth="5" strokeDasharray="219.9114857512855" style={{strokeDashoffset: "420", transition: "stroke-dashoffset 0.3s ease 0s, stroke-dasharray 0.3s ease 0s, stroke 0.3s ease 0s;"}}></circle>
    </svg></div>

    <SemiCircleProgressBar percentage={33} diameter ={150} showPercentValue strokeWidth={20} background={"#202226"} className="progressBar" style={{right:"100%"}} direction={'left'}/>    
    </div> */}
   
 
  <div className="flex-container">
  {Array(1)
    .fill()
    .map(
      (_, rowIdx) => 
      <div className="flex-row">
        {Array(6)
          .fill()
          .map(
            (_, colIdx) => 
            <div className="flex-item">
              <div className="card">
                <div className="card-content">
                  <h4>Sensor {rowIdx * 6 + colIdx + 1}</h4>
                                  <div className='progBarContainer'>
                    <SemiCircleProgressBar percentage={rowIdx*3+colIdx*10} diameter ={200} showPercentValue strokeWidth={20} background={"#202226"} className="progressBar" style={{right:"100%"}}/>    
                    </div>
                </div>
              </div>
            </div>
          
          )
          }
      </div>
    
    )
    }
</div>
<LiveGraph />
    </div>
  );
}

export default App;
