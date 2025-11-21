import Testlib from './NativeTestlib';

export function getComputerName(): string {
  return Testlib.getComputerName();
}

export function getOSVersion(): string {
  return Testlib.getOSVersion();
}

export function setToClipBoard(value: string): boolean {
  return Testlib.setToClipBoard(value)
}

export function setGenericPassword(service: string, username: string, password: string) {
  return Testlib.setGenericPassword(service, username, password)
}

export function getGenericPassword(service: string): Promise<{ username: string; password: string }> {
  return Testlib.getGenericPassword(service);
}

export function resetGenericPassword(service: string) {
  return Testlib.resetGenericPassword(service)
}

export function deleteKeychainEntriesWithPrefix(prefix: string) {
  return Testlib.deleteKeychainEntriesWithPrefix(prefix)
}

export function getBatteryLife(): number {
  return Testlib.getBatteryLife()
}

export function writeToFile(filename: string, filecontent: string): Promise<boolean> {
  return Testlib.writeToFile(filename, filecontent)
}

export function showAlert(title: string, message: string): Promise<void> {
  return Testlib.showAlert(title, message);
}

export function showConfirm(title: string, message: string): Promise<boolean> {
  return Testlib.showConfirm(title, message);
}
