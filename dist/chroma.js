"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const request = require("request-promise-native");
const keyboard_1 = require("./keyboard");
const CHROMA_URL = 'http://localhost:54235/razer/chromasdk';
class Chroma {
    constructor() {
        this.initialized = false;
    }
    async initialize(options) {
        return request.post({ uri: CHROMA_URL, json: options })
            .then((response) => {
            if (response && response.uri && response.sessionid) {
                const { uri, sessionid } = response;
                this.sessionId = sessionid;
                this.sessionUri = uri;
                this.initialized = true;
                this.keyboard = new keyboard_1.Keyboard(uri);
                return true;
            }
            this.initialized = false;
            return false;
        })
            .catch((error) => {
            console.log(`Could not initialize Razer Chroma SDK. Error was:`, error);
            this.initialized = false;
            return false;
        });
    }
    async uninitialize() {
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
exports.Chroma = Chroma;
//# sourceMappingURL=chroma.js.map