'use strict';

const { Chroma } = require('./dist/chroma')

let c = new Chroma()

async function test() {
    const init = await c.initialize({
        'title': 'Razer Chroma SDK RESTful Test Application',
        'description': 'This is a REST interface test application',
        'author': {
            'name': 'Chroma Developer',
            'contact': 'www.razerzone.com'
            },
        'device_supported': [
            'keyboard',
            'mouse',
            'headset',
            'mousepad',
            'keypad',
            'chromalink'],
        'category': 'application'
    })

    console.log(`Init: ${init}`);

    const deinit = await c.uninitialize();

    console.log(`Deinit: ${deinit}`);

    const none = await c.keyboard.setNone();

    console.log(none);

    setTimeout(() => {}, 5000000)
}

test();