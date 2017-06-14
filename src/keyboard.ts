import * as request from 'request-promise-native';

export class Keyboard {
  private uri: string;

  constructor(uri: string) {
    this.uri = `${uri}/keyboard`;
  }

  public async setNone() {
    const options = {
      effect: 'CHROMA_NONE'
    }

    return request.post({ uri: this.uri, json: options});
  }

  // public async setBreathing(thisColor, thatColor) {

  // }

  // public async setBreathingRandom() {

  // }

  // public async setReactive(thisColor) {

  // }

  // public async setSpectrumCycling() {

  // }

  // public async setStarlight(thisColor, thatColor) {

  // }

  // public async setWave('leftToRight') {

  // }

  // public async setStatic(thisColor) {

  // }
}
