# Chroma for Node
This is a native C++ Wrapper for the Chroma SDK, currently only supporting Keyboard. It's a modernized fork of [Chrode](https://github.com/WolfspiritM/Chrode), extending it with a metric ton of features, making it more flexible, and all around ensuring that it's ready for production. 

![](https://cloud.githubusercontent.com/assets/1426799/22614229/5ed1eb96-ea34-11e6-856e-c1d80ee38a08.gif)


## Usage
For more details, check out the samples in `./samples`! All parameters are also documented inline in JSDOC/ESDOC.

```
npm install razer-chroma
```

```js
const chroma = require('razer-chroma')

if (chroma.initialize()) {

  const thisColor = { red: 255, green: 0, blue: 20 }
  const thatColor = { red: 255, green: 0, blue: 20 }

  const {Keyboard} = chroma

  // Go ahead, go add some effects!
  Keyboard.setBreathing(thisColor, thatColor)
  Keyboard.setBreathingRandom()
  Keyboard.setReactive(thisColor)
  Keyboard.setSpectrumCycling()
  Keyboard.setStarlight(thisColor, thatColor)
  Keyboard.setWave('leftToRight')
  Keyboard.setStatic(thisColor)

  // Later
  chroma.terminate()
}
```

## License
MIT, please see `LICENSE.md` for details.
