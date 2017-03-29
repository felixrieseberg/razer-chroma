const chroma = require('../boot')
const utils = require('./utils')

const initialize = chroma.initialize()

if (initialize) {
  chroma.Keyboard.setStarlight({red: 255, green: 0, blue: 0}, {red: 255, green: 0, blue: 0})
  utils.pressKeyToExit(chroma)
} else {
  console.log(`Failed to initialize!`)
}
