const chroma = require('../boot')
const utils = require('./utils')

const initialize = chroma.initialize()

if (initialize) {
  chroma.Keyboard.setSpectrumCycling()
  utils.pressKeyToExit()
} else {
  console.log(`Failed to initialize!`)
}
