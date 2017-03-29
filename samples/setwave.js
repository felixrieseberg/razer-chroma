const chroma = require('../boot')
const utils = require('./utils')

const initialize = chroma.initialize()

if (initialize) {
  chroma.Keyboard.setWave('rightToLeft')
  utils.pressKeyToExit(chroma)
} else {
  console.log(`Failed to initialize!`)
}
