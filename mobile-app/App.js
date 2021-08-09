import { StatusBar } from 'expo-status-bar';
import React, { useEffect, useState } from 'react';
import { Pressable, StyleSheet, Text, TextInput, View } from 'react-native';
import { AntDesign } from '@expo/vector-icons';
import { Camera } from 'expo-camera';

const sizeIcons = 100;
const CarControl = ({direction, urlEnpoint}) => {
  let url = urlEnpoint;
  const press = () => {
    let tmp_direction = direction;
    if(direction === "right"){
      tmp_direction = "left";
    }else if(direction === "left"){
      tmp_direction = "rigth";
    }
    fetch(url+"/"+tmp_direction);
    console.log(url+"/"+tmp_direction);
  }

  const release = () => {
    fetch(url+"/break");
    return;
  }
  return (
    <Pressable onPressIn={press} onPressOut={release} style={styles.RCButton}>
      <AntDesign name={"caret"+direction} size={sizeIcons} color="blue" />
    </Pressable>
  );
}
export default function App() {
  // const sizeIcons = 60;
  const [urlEnpoint, seturlEnpoint] = useState("http://192.168.1.126")
  const [hasPermission, setHasPermission] = useState(null);
  const [type, setType] = useState(Camera.Constants.Type.back);

  useEffect(() => {
    (async () => {
      const { status } = await Camera.requestPermissionsAsync();
      setHasPermission(status === 'granted');
    })();
  }, []);

  return (
    <View style={styles.container}>
      <TextInput onChangeText={seturlEnpoint} value={urlEnpoint} style={styles.textInput}/>
      <View style={styles.controlBox}>
        <CarControl direction="up" urlEnpoint={urlEnpoint} />
        <View style={styles.directionButtons}>
          <CarControl direction="left" urlEnpoint={urlEnpoint} />
          <CarControl direction="right" urlEnpoint={urlEnpoint} />
        </View>
        <CarControl direction="down" urlEnpoint={urlEnpoint} />
      </View>
      <Camera style={{ flex:1, width: "100%", borderWidth: 1}} type={Camera.Constants.Type.back}></Camera>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  directionButtons: {    
    flexDirection: "row",
    justifyContent: "center",
  },
  textInput:{
    height: 40,
    margin: 12,
    borderWidth: 1,
    borderRadius: 10,
    padding: 10,
    margin: 10,
    fontSize: 25
  },
  RCButton:{
    padding: 20,
    borderWidth: 1
  },
  controlBox: {    
    backgroundColor: "grey",
    alignItems: 'center',
    width: "80%",
    borderRadius: 50,
    margin: 10
  }
});
