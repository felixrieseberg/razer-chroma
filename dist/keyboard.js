"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const request = require("request-promise-native");
class Keyboard {
    constructor(uri) {
        this.uri = `${uri}/keyboard`;
    }
    async setNone() {
        const options = {
            effect: 'CHROMA_NONE'
        };
        return request.post({ uri: this.uri, json: options });
    }
}
exports.Keyboard = Keyboard;
//# sourceMappingURL=keyboard.js.map