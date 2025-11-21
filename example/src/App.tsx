import { useState } from 'react';
import { Text, View, StyleSheet, Button } from 'react-native';
import { getComputerName, getOSVersion, setToClipBoard, setGenericPassword, getGenericPassword, resetGenericPassword, getBatteryLife, writeToFile, showAlert, showConfirm } from 'testlib';

const result = getComputerName();
const OSVersion = getOSVersion()
const batteryLife = getBatteryLife()

export default function App() {
  const [username, setUsername] = useState("");
  const [password, setpassword] = useState("");
  const [writeToFileResult, setWriteToFileResult] = useState("false")
  const [alertResult, setAlertResult] = useState("false")

  const handleWriteToFile = async () => {
    const result = await writeToFile("toto", "toto")
    if (result) {
      setWriteToFileResult("true")
    } else {
      setWriteToFileResult("false")
    }
  }

  const handleShowAlert = async () => {
    await showAlert("custom titre", "custom message")
  }

  const handleShowConfirm = async () => {
    try {
      const result = await showConfirm("custom title", "custom message")
      if (result) {
        setAlertResult("true")
      } else {
        setAlertResult("false")
      }
    } catch (e) {
      setAlertResult(e.message)
    }
  }

  return (
    <View style={styles.container}>
      <Text>Computer Name : {result}</Text>
      <Text>OS Version : {OSVersion}</Text>
      <Text>Battery Percentage : {batteryLife} %</Text>
      <Button title='Copy "TOTO"' onPress={() => setToClipBoard("TOTO")} />
      <Button title='Write to file' onPress={() => handleWriteToFile()} />
      <Text>WriteToFileResult : {writeToFileResult}</Text>
      <Button title="Set Generic Password" onPress={() => setGenericPassword("service", "username", "password")} />
      <Button
        title="Display password"
        onPress={async () => {
          try {
            const credentials = await getGenericPassword("service");
            setUsername(credentials.username);
            setpassword(credentials.password);
          } catch (error) {
            console.error("Error getting password:", error);
          }
        }}
      />
      <Button title="Reset Generic Password" onPress={() => resetGenericPassword("service")} />
      <Text>Username : {username}</Text>
      <Text>Password : {password}</Text>
      <Button title="Show Alert" onPress={() => handleShowAlert()} />
      <Button title="Show Confirm" onPress={() => handleShowConfirm()} />
      <Text>Confirm Result : {alertResult}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
