import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  getComputerName(): string;
  getOSVersion(): string;
  setToClipBoard(value: string): boolean;
  setGenericPassword(service: string, username: string, password: string): Promise<boolean>;
  getGenericPassword(service: string): Promise<{ username: string; password: string }>;
  resetGenericPassword(service: string): Promise<boolean>;
  deleteKeychainEntriesWithPrefix(prefix: string): Promise<void>;
  getBatteryLife(): number
  writeToFile(filename: string, filecontent: string): Promise<boolean>
  showAlert(title: string, message: string): Promise<void>
  showConfirm(title: string, message: string): Promise<boolean>
}

export default TurboModuleRegistry.getEnforcing<Spec>('Testlib');
