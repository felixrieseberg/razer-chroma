# Chroma for Node
This is a native C++ Wrapper for the Chroma SDK, currently only supporting Keyboard. It's a modernized fork of [Chrode](https://github.com/WolfspiritM/Chrode), extending it with a metric ton of features.

## Usage

```
npm install razer-chroma
```

```js
const chroma = require('razer-chroma')

if (chroma.initialize()) {
  // Later
  chroma.terminate()
}

## License
MIT, please see `LICENSE.md` for details.
