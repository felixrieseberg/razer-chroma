import * as request from 'request-promise-native';

import { Keyboard } from './keyboard';

const CHROMA_URL = 'http://localhost:54235/razer/chromasdk';

export type ChromaDeviceName = 'keyboard' | 'mouse' | 'headset' | 'mousepad' | 'keypad' | 'chromalink';

export interface ChromaOptions {
  title: string;
  description: string;
  author: {
    name: string;
    contact: string;
  }
  device_supported: Array<ChromaDeviceName>;
  category: 'application' | 'game';
}

export interface ChromaColor { red: number; green: number; blue: number; }

export class Chroma {
  public initialized: boolean = false;
  public sessionId?: string;
  public sessionUri?: string;
  public keyboard?: Keyboard;

  public async initialize(options: ChromaOptions): Promise<boolean> {
    return request.post({ uri: CHROMA_URL, json: options })
      .then((response) => {
        if (response && response.uri && response.sessionid) {
          const { uri, sessionid } = response;
          this.sessionId = sessionid;
          this.sessionUri = uri;
          this.initialized = true;
          this.keyboard = new Keyboard(uri);

          return true;
        }

        this.initialized = false;
        return false;
      })
      .catch((error: Error) => {
        console.log(`Could not initialize Razer Chroma SDK. Error was:`, error);

        this.initialized = false;
        return false;
      })
  }

  public async uninitialize(): Promise<string> {
    if (!this.sessionUri || !this.initialized) {
      return Promise.resolve('Not initialized');
    }

    return request.delete({ uri: this.sessionUri, json: true })
      .then((response) => {
        const { result } = response;

        if (result === 0) {
          this.initialized = false;
        }

        return result;
      });
  }
}
